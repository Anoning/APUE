#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
#include <error.c>

#define NTHR 8
#define NUMNUM 8000000L
#define TNUM (NUMNUM/NTHR)

long nums[NUMNUM];
long snums[NUMNUM];




pthread_barrier_t b;

/*
 *	compare two long integers (helper function for heapsort)
 */

int complong(const void *arg1, const void *arg2)
{
	long l1 = *(long *)arg1;
	long l2 = *(long *)arg2;

	if (l1 == l2)
		return 0;
	else if (l1 < l2)
		return -1;
	else
		return 1;

}

/*
 *	worker thread to sort a portion of the set of numbers
 */
void *thr_fn(void *arg)
{
	long idx = (long)arg;

	heapsort((void *)&nums[idx], (size_t)TNUM, (size_t)sizeof(long), &complong);
	pthread_barrier_wait(&b);

	return ((void*)0);
}
/*
 *	merge the result of the individual sorted ranges
 */
void merge()
{
	long idx[NTHR];
	long i, minidx, sidx, num;

	for (i = 0; i < NTHR; i++)
		idx[i] = i * TNUM;
	for (sidx = 0; sidx < NUMNUM; sidx++){
		num = LONG_MAX;
		for (i = 0; i < NTHR; i++){
			if((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num)){
				num = nums[idx[i]];
				minidx = i;
			}
		}
		snums[sidx] = nums[idx[minidx]];
		idx[minidx]++;
	}

}

int main()
{
	unsigned long	i;
	int err;
	pthread_t tid;

	srandom(1);
	for (i = 0; i < NUMNUM; i++)
		nums[i] = random();

	pthread_barrier_init(&b, NULL, NTHR+1);
	for (i = 0; i < NTHR; i++){
		err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
		if (err != 0)
			err_exit(err, "can't create thread");
	}
	pthread_barrier_wait(&b);
	merge();

	for (i = 0; i < NUMNUM; i++)
		printf("%ld\n", snums[i]);

	exit(0);

}

#include "apue.h"
#include <error.c>

#ifdef SOLARIS
#define PSMD   "ps -a -o pid,ppid,s,tty,comm"
#else
#define PSMD   "ps -o pid,ppid,state,tty,command"
#endif

int main(void)
{
	pid_t pid;

	if ((pid = fork())<0)
		err_sys("fork error");
	else if (pid == 0)
		exit(0);

	sleep(4);
	system(PSMD);

	exit(0);
}

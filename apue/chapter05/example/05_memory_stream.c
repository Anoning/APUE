#include "apue.h"
#include <error.c>
#define BSZ 48

int main()
{
	FILE *fp;
	char buf[BSZ];

	/* first */
	memset(buf, 'a', BSZ-2);
	buf[BSZ-2]='\0';
	buf[BSZ-1]='X';

	/* create stream for buffer */
	if((fp=fmemopen(buf, BSZ, "w+"))==NULL)
		err_sys("fmemopen error");
	printf("inital buffer contents: %s\n", buf);

	fprintf(fp, "hello, world");
	printf("before flush: %s\n", buf);
	fflush(fp);                         /* flush */
	printf("after fflush: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	/* second */
	memset(buf, 'b', BSZ-2);
	buf[BSZ-2]='\0';
	buf[BSZ-1]='X';
	fprintf(fp, "hello, world");
	fseek(fp, 0, SEEK_SET);            /* flush */
	printf("after fseek: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	/* third */
	memset(buf, 'c', BSZ-2);
	buf[BSZ-2]='\0';
	buf[BSZ-1]='X';
	fprintf(fp, "hello, world");
	fclose(fp);                       /* flush */
	printf("after fclose: %s\n", buf);
	printf("len of string in buf = %ld\n", (long)strlen(buf));

	return(0);
}

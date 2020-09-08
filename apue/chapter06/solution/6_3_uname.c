#include "apue.h"
#include<sys/utsname.h>
#include<error.c>

int main(void)
{
	struct utsname buf;

	if(uname(&buf) == -1)
		err_sys("uname error");
	printf("sysname: %s\n", buf.sysname);
	printf("nodename: %s\n", buf.nodename);
	printf("release: %s\n", buf.release);
	printf("version: %s\n", buf.version);
	printf("machine: %s\n", buf.machine);
	exit(0);
}


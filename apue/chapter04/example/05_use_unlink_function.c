#include"apue.h"
#include<fcntl.h>
#include<error.c>

int main(void)
{
	if(open("tempfile", O_CREAT|O_RDWR)<0)
		err_sys("open error");
	if(unlink("tempfile")<0)
		err_sys("unlink error");
	printf("file unlinked\n");

	sleep(15);
	printf("done");
	exit(0);
}

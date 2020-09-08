#include "apue.h"
#include <error.c>

int main(void)
{
	pid_t pid;

	if((pid=fork())<0)
		err_sys("fork error");
	else if( pid ==0 )
	{
		fclose(stdout);
		char *buf="goodbye";
		write(STDOUT_FILENO, buf, sizeof(buf));
	}

}

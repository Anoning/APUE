#include "apue.h"
#include <sys/wait.h>
#include <error.c>

int main(void)
{
	pid_t pid;
	int status;

	if((pid = fork())<0)
		err_sys("fork error1");
	else if (pid == 0)
		exit(7);
	if (wait(&status) == -1) /* wait for child */
		err_sys("wait error1");
	pr_exit(status);


	if((pid== fork())<0)
		err_sys("fork error2");
	else if (pid == 0)
		abort();         /* generates SIGABORT */
	if (wait(&status) == -1)
		err_sys("wait error2");
	pr_exit(status);


	if((pid== fork())<0)
                err_sys("fork error3");
        else if (pid == 0)
		status /= 0;     /* divide by 0 generates SIGFPE */
	if (wait(&status) == -1)
		err_sys("wait error3");
	pr_exit(status);

	exit(0);
}


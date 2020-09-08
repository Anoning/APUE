/*
 *	fork a chile process, but don't want to wait for the termination of 
 *	chile process and also don't want the child process to be in a deadlock 
 *	state until the parent process terminates
 *
 *	use twice fork function to avoid zombie(deadlock process)
 */

#include "apue.h"
#include <sys/wait.h>
#include <error.c>

int main(void)
{
	pid_t pid;
	if((pid = fork()) <0){	
		err_sys("fork error");
	}else if (pid == 0){	/* first child */	
		if((pid = fork())<0) /* second child */
			err_sys("fork error");
		else if (pid > 0)
			exit(0); /* second child's parent died */
	

	/* and then second child's parent become init process*/
	
	sleep(2);
	printf("second child, parent pid = %ld\n", (long)getppid());
	exit(0);
	}

	if (waitpid(pid, NULL, 0) != pid) /* wait for first child */
		err_sys("waitpid error");
	exit(0);
}

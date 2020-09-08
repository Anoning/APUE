#include "apue.h"
#include <error.c>

void check_ids(char *);

int main(void)
{
	pid_t pid;
	pid = fork();
	if (pid < 0)
		err_sys("fork error");
	else if (pid == 0){
		check_ids("child before setsid");
		setsid();
		check_ids("child after setsid");
		return EXIT_SUCCESS;
 	}else{
		sleep(1);
		check_ids("parent");
		return EXIT_SUCCESS;
	}

}

void check_ids(char *name){
	
	printf(" %s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
		name, (long)getpid(), (long)getppid(), (long)getpgrp(),
		(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}


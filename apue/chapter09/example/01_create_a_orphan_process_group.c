#include "apue.h"
#include <errno.h>
#include <error.c>

static void sig_hup(int signo)
{
	printf("STGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name)
{
	printf("%s: pid= %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",name,
			(long)getpid(), (long)getppid(), (long)getpgrp(),
			(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(void)
{
	char c;
	pid_t pid;

	pr_ids("parent");
	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid > 0){	/* parent */
		sleep(5);	/* sleep to let child stop itself */
	}else{
		pr_ids("child");
		signal(SIGHUP, sig_hup);
		kill(getpid(), SIGTSTP); /*stop ourself*/
		pr_ids("child");
		int getnum;
		if ((getnum=read(STDIN_FILENO, &c, 1) )!= 1)
			printf("read error %d on controlling TTY\n",errno);
		printf("getnum: %d\n",getnum);
	}

	exit(0);
}


#include "apue.h"
#include <error.c>

void print_status(siginfo_t infop);

int main(void)
{
	setlinebuf(stdout);

	int num = 1;
	pid_t pid;
	siginfo_t infop;

	if ((pid = fork()) < 0)
		err_sys("fork1 error");
	else if (pid == 0)
		exit(7);

	if(waitid(P_PID, pid, &infop, WEXITED | WSTOPPED) == -1)
		err_sys("waitid1 error");
	print_status(infop);

	if((pid == fork())<0)
		err_sys("fork2 error");
	else if (pid == 0)
		abort();
	waitid(P_PID, pid, &infop, WEXITED | WSTOPPED);
		
	print_status(infop);


	if((pid = fork())<0)
		err_sys("fork3 error");
	else if (pid == 0)
		num /= 0;
	if(waitid(P_PID, pid, &infop, WEXITED | WSTOPPED) == -1)
		err_sys("waitid3 error");
	print_status(infop);


}

void print_status(siginfo_t infop){
	switch (infop.si_code){
		case CLD_EXITED:
			printf("normal termination, exit status = %d\n", infop.si_status);
			break;
		case CLD_KILLED:
			printf("abnormal termination, signal number = %d\n", infop.si_status);
			break;
		case CLD_DUMPED:
			printf("abnormal termination, signal number = %d (core file generated)\n", infop.si_status);
			break;
		default:
			err_quit("Unexpected infop.si_code %d\n", infop.si_code);
	}


}

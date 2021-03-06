#include "apue.h"
#include "common.h"
#include <assert.h>
#include <sys/select.h>

#define BFSZ	128

int main()
{
	int 	pid, pipe_in, pipe_out;
	int 	pipe_fds[2];
	char	msg[] = "hello";

	sys_chk(pipe(pipe_fds));

	pipe_out = pipe_fds[0];
	pipe_in  = pipe_fds[1];

	sys_chk(pid = fork());

	if (pid == 0){
		sys_chk(close(pipe_in));
		sys_chk(close(pipe_out));

		return EXIT_SUCCESS;

	}else{
		fd_set	readfds, writefds, exceptfds;
		sys_chk(close(pipe_out));
		sleep(1);

		FD_ZERO(&readfds);
		FD_SET(pipe_in, &readfds);
		FD_ZERO(&writefds);
		FD_SET(pipe_in, &writefds);
		FD_ZERO(&exceptfds);

		sys_chk(select(pipe_in + 1, &readfds, &writefds, &exceptfds, NULL));
		if (FD_ISSET(pipe_in, &readfds))
			printf("ready for reading\n");
		if (FD_ISSET(pipe_in, &writefds))
			printf("ready for writing\n");
		if (FD_ISSET(pipe_in, &exceptfds))
			printf("Exception\n");

		assert(write(pipe_in, msg, sizeof msg) == sizeof msg);

		sys_chk(close(pipe_in));
		return EXIT_SUCCESS;
	}
}

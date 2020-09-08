#include "apue.h"
#include "common.h"
#include <assert.h>
#include <poll.h>

#define BFSZ 128

int main()
{
	int	pid, pipe_in, pipe_out;
	int	pipe_fds[2];
	char	buf[BFSZ] = "hello,world";

	sys_chk(pipe(pipe_fds));
	pipe_out = pipe_fds[0];
	pipe_in  = pipe_fds[1];

	sys_chk(pid = fork());

	if (pid == 0){
		sys_chk(close(pipe_in));
		return EXIT_SUCCESS;
	}else{
		struct pollfd	fds[1];

		sys_chk(close(pipe_out));
		fprintf(stderr, "Sleeping...");
		sleep(5);
		fprintf(stderr, "Done.\n");

		fds[0].fd = pipe_in;
		fds[0].events = POLLIN|POLLOUT;

		sys_chk(poll(fds, 1, 0));
		if (fds[0].revents & POLLIN)
			printf("ready for reading\n");
		if (fds[0].revents & POLLOUT)
			printf("ready for writing\n");
		if (fds[0].revents & POLLERR)
			printf("poll error\n");
		if (fds[0].revents & POLLHUP)
			printf("POLLHUP\n");
		if (fds[0].revents & POLLNVAL)
			printf("POLLNVAL\n");

		fprintf(stderr, "Got from child: %s\n", buf);
		return EXIT_SUCCESS;

	}
}

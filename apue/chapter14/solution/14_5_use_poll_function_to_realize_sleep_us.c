#include <poll.h>

void sleep_us(unsigned int nusecs)
{
	struct pollfd	dummy;
	int		timeout;

	if ((timeout = nusecs / 100) <= 0)
		timeout = 1;
	poll(&dummy, 0, timeout);
}

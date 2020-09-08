#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void charatatime(char *);

int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0){
		exit(0);
	}else if (pid == 0){
		charatatime("output from child aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	}else{
		charatatime("output from parent bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");
	}
	exit(0);
}

static void charatatime(char *str)
{
	char *ptr;
	char c;
	setbuf(stdout, NULL);
	for (ptr = str; (c = *ptr++) !=0;)
		putc(c,stdout);
}

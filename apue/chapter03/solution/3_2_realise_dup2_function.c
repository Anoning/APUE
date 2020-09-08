/*
 *	dup2(): if oldfd=newfd ,don't need to close this fd, and return oldfd,
 *		if oldfd!=newfd, first close newfd , then copy oldfd to this 
 *		newfd
 */


#include "apue.h"
#include<error.c>
#include<unistd.h>
#include<stdlib.h>
int my_dup2(int oldfd, int newfd);

int main(int argc, char *argv[])
{
	if(argc != 3)
		err_quit("you should input 2 parameter : oldfd and newfd");
	
	int fd = my_dup2(atoi(argv[1]) ,atoi(argv[2]) );
	
	if(fd>0){
		write(STDOUT_FILENO, "SUCCESS", 7); 
		return 0;
	}
	else{
		write(STDOUT_FILENO, "error", 5);
		return 0;
	}
}

int my_dup2(int oldfd, int newfd)
{
	if(oldfd<0 || oldfd>256)
		err_quit(" oldfd error");
	
	int index = 0;
	int record_open_fd[newfd];

	if((record_open_fd[index]=dup(oldfd))==-1)
		err_quit("error while dup");

	else close(record_open_fd[index]);

	if( oldfd = newfd)
		return oldfd;

	else close(newfd);
	for( index = 0; index <= newfd; index++)
	{	
		if((record_open_fd[index]=dup(oldfd)) = -1)
			err_quit("error while dup");
		else{
			if(record_open_fd[index] == newfd){
				/* close all opened fd */
				for(int i=0;i<index;i++)
					close(record_open_fd[i]);
				return newfd;
			}
		}
	}
	return -1;

}




#include "apue.h"
#include "common.h"
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	for (int i = 0; i < 5; ++i){
		key_t	key;
		int	queue_id;

		/* create a message queue */
		sys_chk(key = ftok("/dev/null", i));
		sys_chk(queue_id = msgget(key,  IPC_CREAT|S_IWUSR|S_IRUSR));

		printf("queue id: %d\n", queue_id);

		/* delete the queue */
		sys_chk(msgctl(queue_id, IPC_RMID, NULL));
	}

	char msg[] = "hello";
	for (int i = 0; i < 5; ++i){
		int queue_id;

		/* create a message with a key IPC_PRIVATE */
		sys_chk(queue_id = msgget(IPC_PRIVATE, IPC_CREAT|S_IWUSR|S_IRUSR));

		/* place a message on the queue */
		sys_chk(msgsnd(queue_id, msg, sizeof(msg), 0));


	}
	return EXIT_SUCCESS;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shm_com.h"

int main(int argc, char *argv[])
{
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	char buffer[BUFSIZ];
	int shmid;

	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);

	if(shmid == -1)
	{
		printf("shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)0, 0)
	{
		printf("shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("memory attached at %X\n", (int)shared_memory);

	shared_stuff = (struct shared_use_st *)shared_memory;
	while(running)
	{
		while(shared_stuff -> written_by_you == 1)
		{
			sleep(1);
			printf("waiting for client \n");
		}
	
		printf("enter some text:\n");
		fgets(buffer, BUFSIZ, stdin);

		strncpy(shared_stuff -> some_text, buffer, TEXT_SZ);
		shared_stuff -> written_by_you = 1;
	
		if(strncmp(buffer, "end", 3) == 0)
			running = 0;
	}

	if(shmdt(shared_memory) == -1)
	{
		printf("shmdt fail\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}	


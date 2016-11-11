#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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
	int shmid;

	srand((unsigned int) getpid());
	
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
	if(shmid == -1)
	{
		printf("shmget fail\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *) - 1)
	{
		printf("shmat fail\n");
		exit(EXIT_FAILURE);
	}
	printf("\nmemory attached at %X\n", (int)shared_memory);

	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff -> written_by_you = 0;
	while(running)
	{
		if(shared_stuff -> written_by_you)
		{
			printf("you wrote: %s ", shared_stuff -> some_text);
			sleep(rand() % 4);
			shared_stuff -> written_by_you = 0;
			if(strncmp(shared_stuff -> some_text, "end", 3) == 0)
				running =0;
		}
	}
}



#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int file_pipes[2];
	char buf[BUFSIZ + 1];
	pid_t fork_result;
	char some_data[] = "1234";
	memset(buf, '\0', sizeof(buf));

	if(pipe(file_pipes) == 0)
	{
		fork_result = fork();
		if(fork_result == -1)
		{
			printf("fork fail\n");
			exit(EXIT_FAILURE);
		}
	}

	if(fork_result == 0)
	{
		write(file_pipes[1], some_data, strlen(some_data));
		printf("process:%d write:%s\n", fork_result, some_data);
//		exit(EXIT_SUCCESS);
	}
	else
	{
		wait();
		read(file_pipes[0], buf, BUFSIZ);
		printf("process:%d read:%s\n", fork_result, buf);
	}
	
	printf("%d exit\n", fork_result);
	exit(EXIT_SUCCESS);
}

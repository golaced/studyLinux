#define _REENTRANT

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char message[] = "hello thread word\n";
void *thread_function(void *arg);

int main()
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
	if(res != 0)
	{
		perror("thread create fail\n");
		exit(EXIT_FAILURE);
	}
	printf("waiting for thread to finish\n");
	res = pthread_join(a_thread, &thread_result);
	if(res != 0)
	{
		perror("thread join fail\n");
		exit(EXIT_FAILURE);
	}
	printf("thread join it returned %s\n", (char *)thread_result);
	printf("message is now %s\n", message);
}

void *thread_function(void *arg)
{
	printf("thread_function is running . argument was %s\n", (char *)arg);
	sleep(3);
	strcpy(message, "bye\n");
	pthread_exit("thank you for the cpu time\n");
}

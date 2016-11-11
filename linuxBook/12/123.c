#define _REENTRANT

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char message[] = "hello thread word\n";
void *thread_function(void *arg);
int run_now = 1;

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
	
	int print_count1 = 0;
	while(print_count1++ < 20)
	{
		if(run_now == 1)
		{
			printf("1\n");
			run_now = 2;
		}
		else
		{
			sleep(1);
		}
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
	int print_count2 = 0;

	while(print_count2++ < 30)
	{
		if(run_now == 2)
		{
			printf("2\n");
			run_now = 1;
		}
		else
		{
			sleep(1);	
			printf("thread sleep 1\n");
		}
	}
	pthread_exit("pthread_exit\n");
}

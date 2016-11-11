#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
int replace();
int systemf();
int copyf();
int redirect(char *fileName);
int signalh();
void ouchh(int sig);

int main(int argc, char *argv[])
{
	int flag = 4;
	int i = 0;

	switch(flag)
	{
	case 0:
		systemf();
		break;
	case 1:
		replace();
		break;
	case 2:
		copyf();
		break;
	case 3:
		if(argc == 2)
			redirect(argv[1]);
		else
			printf("redirect usage fail\n");
		break;
	case 4:
		signalh();
		break;
	default:
		{
			printf("argc = %d\n", argc);
			for(i = 0; i < argc; i++)
			{
				printf("argv[%d],%s\n",i,argv[i]);
			}
			printf("switch default\n");;
			break;
		}
	}
	exit(0);
}

/*signal receive*/
void ouchh(int sig)
{
	printf("ouch,i got a signal %d\n",sig);
	signal(SIGINT, SIG_DFL);
}
int signalh()
{
	(void)signal(SIGINT, ouchh);
	while(1)
	{
		printf("hello\n");
		sleep(1);
	}
}
/*redirect input output*/
int redirect(char *fileName)
{
	int ch;
	if(!freopen(fileName, "r", stdin))
		printf("could not open fileName\n");
	else
	{
		while((ch = getchar()) != EOF)
		{
			putchar(toupper(ch));
		}
	}
}
/*copy program*/
int copyf()
{
	pid_t pid = 1;
	char *message;
	int n;
	
	pid = fork();
	printf("fork program starting\n");
	switch(pid)
	{
	case -1:
		printf("fork error\n");
		perror("fork failed\n");
		n = 1;
		break;
	case 0:
		message = "this is the child";
		n = 5;
		break;
	default:
		printf("program pid %d\n", pid);
		message = "this is the parent";
		n = 2;
		break;
	}
	for(;n > 0; --n)
	{
		puts(message);
		sleep(1);
	}
	printf("puts message done\n");

	if(pid != 0)
	{
		int stat_val;
		pid_t child_pid;
		
		child_pid = wait(&stat_val);
		printf("child has finished :PID = %d\n", child_pid);
		if(WIFEXITED(stat_val))
			printf("child exited with code %d\n", WEXITSTATUS(stat_val));
		else 
			printf("child terminated abnormally\n");
	}
}
/*replace program*/
int replace()
{
	printf("running ps with execlp\n");
//	execlp("ps","ps","-ax",0);
	printf("done\n");
}
/*system create program*/
int systemf()
{
	printf("running ps with system\n");
	system("ps -ax");
	printf("done\n");
}

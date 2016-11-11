#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int myodc()
{
	FILE *write_fp;
	char buffer[BUFSIZ + 1];

	sprintf(buffer, "once upon a time,...\n");
	write_fp = popen("od -c", "w");
	if(write_fp != NULL)
	{
		fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
		pclose(write_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
int mypsax()
{
	FILE *read_fp;
	char buffer[BUFSIZ + 1];
	int chars_read;

	memset(buffer, '\0', sizeof(buffer));
	read_fp = popen("ps -ax", "r");
	if(read_fp != NULL)
	{
		chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		while(chars_read > 0)
		{
			buffer[chars_read - 1] = '\0';
			printf("reading:-\n%s\n", buffer);
			chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
		}
		pclose(read_fp);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv)
{
	int flg = argc - 1;
	
	switch(flg)
	{
		case 0:
			myodc();
			break;
		case 1:
			mypsax();
			break;
		default:
			break;
	}
}

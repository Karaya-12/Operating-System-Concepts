#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char* argv[])
{
	pid_t pid;
	int f0 = 0, f1 = 1, f2;
	if (argv[1] < 0)                                                 //Argument Check --> Non-negative Number
	{
		fprintf(stderr, "Non-negative Number Requested !");
		exit(-1);
	}
	pid = fork();
	if (pid < 0)                                                     //Child Process Check
	{
		fprintf(stderr, "Fork Failed !");
		exit(-1);
	}
	else if (pid == 0)
	{
		printf("Number of Arguments = %d\n", atoi(argv[1]));         //Alphanumeric to Integer
		printf("Fibonacci Sequence : 0 1 ");
		for (int i = 2; i <= atoi(argv[1]); i++)
		{
			f2 = f0 + f1;
			f0 = f1;
			f1 = f2;
			printf("%d ", f2);
		}
		printf("\nChild Process Completed\n");
	}
	else
	{
		wait(NULL);
		printf("Parent Process Exited\n");
	}
	return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
	pid_t status = fork();
	if(status < 0)
	{
		printf("Couldn't create.\n");
		exit(1);
	}
	else if(status == 0)
	{
		printf("CHILD : Here we are in the child. My Pid = %d, Parent Pid = %d\n", getpid(), getppid());
		char *newargv[] = { "filename", "/home", NULL};
		char *newenviron[] = { NULL};
		if(0 > execve("/bin/ls", newargv, newenviron))
		{
			printf("couldn't run");
			exit(1);
		}

	}
	else
	{
		printf("PARENT : Child Pid = %d My Pid = %d, Parent Pid = %d\n", status, getpid(), getppid());
	}
	return 0;
}
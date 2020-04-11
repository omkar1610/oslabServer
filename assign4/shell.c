#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


  


int main(int argc, char const *argv[])
{
	char buf[PATH_MAX] = "";

	if(getcwd(buf, PATH_MAX)==NULL)
		perror("getcwd error");

	while(1)
	{
		printf("%s>", buf);
		// fflush(stdout);
		char *input;
		scanf("%m[^\n]", &input);
		getchar();
		printf("Entered %s\n", input);


	}

	return 0;
}
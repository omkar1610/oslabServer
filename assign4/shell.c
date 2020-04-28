#include "shell.h"

int main(int argc, char const *argv[], char const *envp[])
{
	
	FILE *file = fopen(".myshell-history", "a+");
	fseek(file, 0, SEEK_END);// a+ starts at begining
	clrscr;
	while(1)
	{
		prompt();
		
		//Input Command by user
		char *input;
		scanf("%m[^\n]", &input);
		getchar();
		// printf("Entered %s-\n", input);

		if(input == NULL)
			continue;

		int count = char_count(input, ' ');

		// parse_input(input, count, file, envp);
		my_parser(input, count, file, envp);
	}
	
	fclose(file);

	return 0;
}
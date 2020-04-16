#include "shell.h"

int main(int argc, char const *argv[])
{
	FILE *file = fopen(".myshell-history", "a+");
	fseek(file, 0, SEEK_END);// a+ starts at begining
	clrscr();
	while(1)
	{
		prompt();
		
		//Input Command by user
		char *input;
		scanf("%m[^\n]", &input);
		getchar();
		// printf("Entered %s-\n", input);

		// fprintf(file, "%s\n", input);
		if(input == NULL)
			continue;

		int count = char_count(input, ' ');
		// if(0 < count)
			parse_input(input, count, file);
		// else
			// run_direct_command(input, file);
	}
	fclose(file);

	return 0;
}
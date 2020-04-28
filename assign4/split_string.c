#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int char_count(const char *input, char delim)// Counts no of spaces to get argument count in the command
{
	int count = 0;
	for (int i = 0; input[i]!='\0'; ++i)
		if(input[i] == delim)
			count++;
	return count;

}


int str_to_argv(char *s, int length, char argv[][length+1])
{
	int argc = 0;
	int curr_arg_pos = 0;
	for (int i = 0; i < length; ++i)
	{
		if(s[i] == ' ')
		{
			if(curr_arg_pos != 0)
			{
				argv[argc][curr_arg_pos] = '\0';
				argc++;
				curr_arg_pos = 0;
			}
		}
		else if(s[i] == '\\')
		{
			if(i!=length-1)
				argv[argc][curr_arg_pos++] = s[++i];
		}
		else
		{
			argv[argc][curr_arg_pos++] = s[i];
		}		
	}
	if(curr_arg_pos!=0)
	{
		argv[argc][curr_arg_pos] = '\0';
		argc++;
		curr_arg_pos = 0;
	}
	return argc;
}


int main()
{
	char *s;
	scanf("%m[^\n]",&s);
	getchar();

	int length = strlen(s);
	int count = char_count(s, ' ');
	char argv[count][length+1];

	int argc = str_to_argv(s, length, argv);
	
	printf("argc = %d,argv = ",argc);

	for (int j = 0; j < argc; ++j)
		printf(":%s: ", argv[j]);

	printf("\n");
	return 0;
}
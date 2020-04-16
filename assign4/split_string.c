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
int main()
{
	char *s;
	scanf("%m[^\n]",&s);
	getchar();

	int n = char_count(s, ' ') + 1;
	printf("argc %d\n", n);
	char **argv = malloc((n+1)*sizeof(char *));

	int i = 1;
	argv[0] = strtok(s, " ");
	while(1)
	{
		if((argv[i] = strtok(NULL, " ")) == NULL)
			break;
		i++;
		// printf("%s\n", argv[i-1]);
	}
	while(i--)
		printf("%s\n", argv[i]);
	return 0;
}
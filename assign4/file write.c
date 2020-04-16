#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	FILE *fd = fopen(".myshell-history", "a");
	char f[10];
	scanf("%s", f);
	fprintf(fd, "%s\n", f);
	fprintf(fd, "%s\n", f);
	fclose(fd);

	fd = fopen(".myshell-history", "r");
	char c = fgetc(file); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(file); 
    } 
    printf("\n");
	fclose(fd);
	return 0;
}
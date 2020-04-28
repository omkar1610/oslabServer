#include <stdio.h>
#include <stdlib.h>

int count_line(FILE *file)
{
	int line = 0;
	rewind(file);
	char chr = getc(file);
    while (chr != EOF)
    {
        if (chr == '\n')
        	line++;
        chr = getc(file);
    }
    return line;
}


int main(int argc, char const *argv[])
{
	FILE *fd = fopen(".myshell-history", "a+");
	int line_no = count_line(fd);
	int offset = 5;
	rewind(fd);
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	int i = line_no - offset;
	while (i-- && (nread = getline(&line, &len, fd)) != -1);
	while ((nread = getline(&line, &len, fd)) != -1) {
		printf("%s", line);
	}




	fclose(fd);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

// #include <curses.h>
#include <dirent.h>
#include <time.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <sys/sysmacros.h>

#include <pwd.h>
#include <grp.h>



int char_count(const char *input, char delim)// Counts no of spaces to get argument count in the command
{
	int count = 0;
	for (int i = 0; input[i]!='\0'; ++i)
		if(input[i] == delim)
			count++;
	return count;

}

void prompt()
{
	char path[PATH_MAX] = "";
	if(getcwd(path, PATH_MAX)==NULL)
		perror("getcwd error");

	printf("\033[1;32m" "My Shell:" "\033[1;36m""%s>\t" "\033[0m", path);
	
	fflush(stdout);
}

void clrscr()
{
	// \033 = ESC,  [H = move to top left, [J = clear everything to the end starting from the current position
	printf("\033[H\033[J");
}

void show_help()
{
	printf("Available Commands\n");
	printf("1.clear:\tclear the screen\n");
	printf("2.env:\t\tdisplays all environment parameters\n");
	printf("3.cd <dir>:\tchange to the directory as specfied by the user\n");
	printf("4.pwd:\t\tprints the current directory\n");
	printf("5.mkdir <dir1> <dir2> ...:\t\tcreates a directory(ies)\n");
	printf("6.rmdir <dir1> <dir2> ...:\t\tremoves the directory(ies)\n");
	printf("7.ls <dir1> <dir2> ...(optional -l option):\t\tlists files in current directory\n");
	printf("9.history:\tdisplays the last commands the user ran, with an offset next to each command.\n");
	printf("10.exit:\texits the program\n");
}
  

void cd(char *new_path)
{
	if(chdir(new_path) != 0)
	{
		fprintf(stderr, "cd: %s: ", new_path);
		perror("");
	}

}

void makedir(const char *new_path)
{
	if(mkdir(new_path, 0777) != 0)
	{
		fprintf(stderr, "mkdir: %s: ", new_path);
		perror("");
	}
}

void removedir(const char *new_path)
{
	if(rmdir(new_path) != 0)
	{
		fprintf(stderr, "rmdir: %s: ", new_path);
		perror("");
	}
}

void file_name_print(struct dirent *de)
{
	unsigned char type = de->d_type;

	if(type == 4) //Directory Blue
		printf("\033[1;34m");
	// else if(type == 8)// Executable Green
	// 	printf("\033[1;32m");
	else if(type == 10)	// Link  Cyan
		printf("\033[1;36m");

	printf("%s", de->d_name);
	printf("\033[0m");//Change color to default	
}

void ls(const char *new_path)
{
	struct dirent *de; 
    DIR *dr = opendir(new_path); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        perror("ls");
        return;
    } 
  
    while ((de = readdir(dr)) != NULL) 
    {
    	file_name_print(de);
    	printf("\t");
        // printf("%s\t", de->d_name); 
    }
  	printf("\n");
    closedir(dr);  
}

void show_mode(mode_t mode)
{
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

void long_print_file(char *new_path, const char *file)
{
	char *path = malloc(1 + strlen(new_path) + strlen(file));
	int i;
	for (i = 0; new_path[i] != '\0'; ++i)
		path[i] = new_path[i];

	path[i++] = '/';

	for (int j = 0; file[j] != '\0'; ++i, ++j)
		path[i] = file[j];
	path[i] = '\0';

	// printf("File name %s\n", path);
	
	struct stat buf;
	if(0 != lstat(path, &buf))
	{
		perror("lstat");
		return;
	}
	mode_t mode = buf.st_mode;
	nlink_t hard_link = buf.st_nlink;
	uid_t uid = buf.st_uid;
	gid_t gid = buf.st_gid;
	off_t size = buf.st_size;
	struct timespec tmspc = buf.st_mtim;
	time_t tot_sec = tmspc.tv_sec;
	const time_t *timep = &tot_sec;

	show_mode(mode);	
	printf("\t%lu \t%s \t%s \t%lu", hard_link, getpwuid(uid)->pw_name, getgrgid(gid)->gr_name, size);

    struct tm *timetm = localtime(timep);
    char *month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    printf("\t%s %d %d:%d\t", month[timetm->tm_mon], timetm->tm_mday, timetm->tm_hour, timetm->tm_min);
	
	// printf("\t%s", file);
	// printf("\n");
}

void ls_l(char *new_path)
{
	struct dirent *de; 
    DIR *dr = opendir(new_path); 
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        perror("ls");
        return;
    } 
  
    while ((de = readdir(dr)) != NULL) 
    {
    	// printf("%d  ", de->d_type);
    	long_print_file(new_path, de->d_name);
    	file_name_print(de);
    	printf("\n");
    }
  	// printf("\n");
    closedir(dr);  
}

void run_direct_command(const char *input1, FILE *file) //This will take care of clear, env, pwd, history, exit, ls, cd, help
{
	char *input = malloc(strlen(input1));
	strcpy(input, input1);

	char *cmd = strtok(input, " ");

	if(strcmp(cmd, "clear") == 0)
	{
		fprintf(file, "%s\n", input1);
		
		clrscr(); 
	}
	else if(strcmp(cmd, "env") == 0)
	{

		fprintf(file, "%s\n", input1);
	}
	else if(strcmp(cmd, "pwd") == 0)
	{
		fprintf(file, "%s\n", input1);
		char path[PATH_MAX] = "";
		if(getcwd(path, PATH_MAX)==NULL)
			perror("getcwd error");
		
		printf("%s\n", path);
	}
	else if(strcmp(cmd, "history") == 0)
	{
		fprintf(file, "%s\n", input1);

		rewind(file);
		char c = fgetc(file); 
	    while (c != EOF) 
	    {
	        printf ("%c", c); 
	        c = fgetc(file); 
	    }
	    printf("\n");
		fseek(file, 0, SEEK_END); 
	}
	else if(strcmp(cmd, "exit") == 0)
	{
		fprintf(file, "%s\n", input1);
		fclose(file);
		exit(0);
	}
	else if(strcmp(cmd, "ls") == 0)
	{
		fprintf(file, "%s\n", input1);
	}
	else if(strcmp(cmd, "cd") == 0)
	{
		fprintf(file, "%s\n", input1);
	}
	else if(strcmp(cmd, "help") == 0)
	{
		fprintf(file, "%s\n", input1);
		show_help();
	}
	else 
	{
		printf("Invalid Command. Type help for details\n");
	}
}


void parse_input(const char *input1, const int count, FILE *file)
{
	char *input = malloc(strlen(input1));
	strcpy(input, input1);

	char *cmd = strtok(input, " ");
	if(strcmp(cmd, "clear") == 0)
	{
		fprintf(file, "%s\n", input1);
		
		clrscr(); 
	}
	else if(strcmp(cmd, "env") == 0)
	{

		fprintf(file, "%s\n", input1);
	}
	else if(strcmp(cmd, "pwd") == 0)
	{
		fprintf(file, "%s\n", input1);
		char path[PATH_MAX] = "";
		if(getcwd(path, PATH_MAX)==NULL)
			perror("getcwd error");
		
		printf("%s\n", path);
	}
	else if(strcmp(cmd, "history") == 0)
	{
		fprintf(file, "%s\n", input1);

		rewind(file);
		char c = fgetc(file); 
	    while (c != EOF) 
	    {
	        printf ("%c", c); 
	        c = fgetc(file); 
	    }
	    printf("\n");
		fseek(file, 0, SEEK_END); 
	}
	else if(strcmp(cmd, "exit") == 0)
	{
		fprintf(file, "%s\n", input1);
		fclose(file);
		exit(0);
	}
	else if(strcmp(cmd, "cd") == 0)
	{
		fprintf(file, "%s\n", input1);
		if(count>1)
			printf("Too many arguments for cd. Usage: cd <directory>\n");
		else if(count == 0)
			cd("/home"); // go to home on only cd
		else
		{
			char *args = strtok(NULL, " ");
			cd(args);
		}
	}
	else if(strcmp(cmd, "mkdir") == 0)
	{
		fprintf(file, "%s\n", input1);
		while(1)
		{
			char *args = strtok(NULL, " ");
			if(args == NULL)
				break;
			makedir(args);
		}

	}
	else if(strcmp(cmd, "rmdir") == 0)
	{
		fprintf(file, "%s\n", input1);
		while(1)
		{
			char *args = strtok(NULL, " ");
			if(args == NULL)
				break;
			removedir(args);
		}
	}
	else if(strcmp(cmd, "ls") == 0)
	{
		fprintf(file, "%s\n", input1);
		if(strstr(input1, "-l") == NULL)// NO -l option
		{
			if(count == 0) // only ls is same is ls .
				ls(".");
			else
			{
				while(1)
				{
					char *args = strtok(NULL, " ");
					if(args == NULL)
						break;
					if(args[0] != '-')
					{
						printf("\n%s:\n", args);
						ls(args);
					}
				}
			}
		}
		else
		{
			if(count == 1) //only ls -l is same as ls -l .
			{
				ls_l(".");
			}
			else
			{
				while(1)
				{
					char *args = strtok(NULL, " ");
					if(args == NULL)
						break;
					if(args[0] != '-')
					{
						printf("\n%s:\n", args);
						ls_l(args);
					}
				}
			}
		}
	}
	else if(strcmp(cmd, "help") == 0)
	{
		fprintf(file, "%s\n", input1);
		show_help();
	}
	else
	{
		printf("Invalid Command. Type help for details\n");
	}
}
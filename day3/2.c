#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <string.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


#define MAX_SEQUENCE 10

typedef struct {
	long fib_sequence[MAX_SEQUENCE];
	int sequence_size;
} shared_data;


int main(int argc, char const *argv[])
{


	if (argc != 2) 
    { 
        printf("USAGE : <file> <number>\n"); 
        exit(0); 
    } 
  
    int n = atoi(argv[1]);

    if ( n <= 0  || n > MAX_SEQUENCE) 
    { 
        printf("Enter number between 1 and %d\n", MAX_SEQUENCE); 
        exit(0); 
    } 



	const int SIZE = sizeof(shared_data);
	const char *name = "structure";
	int shm_fd;
	void *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); // returns -1 on failure
	if(shm_fd == -1)
	{
		perror("shm_open");
		exit(EXIT_FAILURE);
	}

	if(ftruncate(shm_fd, SIZE) == -1)//-1 on error
	{
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); //MAP_FAILED returned on error
	if( ptr == (void *) -1)
	{
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	shared_data *tmp = (shared_data *)ptr;
	tmp->sequence_size = n;	

	pid_t pid=fork(); 
	  
	if ( pid<0 ) 
	{ 
		perror("fork");
		exit(EXIT_FAILURE);
	} 
	else if ( pid==0 ) 
	{ 
		shm_fd = shm_open(name, O_RDWR, 0666);
		if(shm_fd == -1)
		{
			perror("shm_open");
			exit(EXIT_FAILURE);
		}
		ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); //MAP_FAILED returned on error
		if( ptr == (void *) -1)
		{
			perror("mmap");
			exit(EXIT_FAILURE);
		}
		shared_data *tmp = (shared_data *)ptr;

		printf("Child Writing\n");
		
		int n = tmp->sequence_size;
		tmp->fib_sequence[0] = 0, tmp->fib_sequence[1] = 1;
		for (int i = 2; i < n; ++i)
			tmp->fib_sequence[i] = tmp->fib_sequence[i-1] + tmp->fib_sequence[i-2];

		return 0;
	}
	else
	{
		wait(NULL);
		printf("Parent Reading\n");
		// ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

		shared_data *tmp = (shared_data *)ptr;
		for (int i = 0; i < n; ++i)
			printf("%ld ", tmp->fib_sequence[i]);
		printf("\n");
		shm_unlink(name);	

		return 0;
	}
}
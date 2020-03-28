#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <string.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


int main(int argc, char const *argv[])
{

	int shm_fd = shm_open("mem", O_CREAT | O_RDWR, 0666); // returns -1 on failure
	// ftruncate(shm_fd, SIZE);//-1 on error

	struct shmid_ds buf;
	int return_v = shmctl(shm_fd, SHM_STAT, &buf);
	printf("%d %d %lu\n", shm_fd, return_v, buf.shm_segsz);

	
}
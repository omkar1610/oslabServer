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

void details(int shmid)
{
  if(shmat(shmid,(void*)0,0) == (void *) -1)
  {
    perror("shmat(no such id)");
    exit(EXIT_FAILURE);
  } 
  
  struct shmid_ds buf;
  if(shmctl(shmid, IPC_STAT, &buf) == -1)
  {
    perror("shmctl");
    exit(EXIT_FAILURE);
  }

  printf("Seg ID = %d\n", shmid);
  printf("Key(in Hex) = %04x\n", buf.shm_perm.__key);
  printf("Mode = %u\n", buf.shm_perm.mode);
  printf("Owner UID = %d\n", buf.shm_perm.uid);
  printf("Size = %lu\n", buf.shm_segsz);
  printf("No of attaches(including this process) = %lu\n", buf.shm_nattch);

}

int main(int argc, char const *argv[])
{
  if (argc != 2) {
       fprintf(stderr, "Usage: %s <shmid>\n", argv[0]);
       exit(EXIT_FAILURE);
  }
  details(atoi(argv[1]));

  return 0;
}
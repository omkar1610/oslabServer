#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
   int pipefd[2], pipe_rev[2];
   pid_t cpid;

   int BUFFER = strlen(argv[1]) + 1;
  char msg[BUFFER];
   
   

   if (argc != 2) {
       fprintf(stderr, "Usage: %s <string> (String within quotes if white char is there)\n", argv[0]);
       exit(EXIT_FAILURE);
   }

   if (pipe(pipefd) == -1) {
       perror("pipe1");
       exit(EXIT_FAILURE);
   }
   if (pipe(pipe_rev) == -1) {
       perror("pipe2");
       exit(EXIT_FAILURE);
   }

   cpid = fork();
   if (cpid == -1) {
       perror("fork");
       exit(EXIT_FAILURE);
   }

   if (cpid == 0) 
   {
      close(pipefd[WRITE]); 
      read(pipefd[READ], msg, BUFFER);
      close(pipefd[READ]);

      // printf("CHILD : %s\n", msg);
      for (int i = 0; i < BUFFER; ++i)
        if(islower(msg[i]))
          msg[i] = toupper(msg[i]);
        else if(isupper(msg[i]))
          msg[i] = tolower(msg[i]);

      // printf("CHILD NEW : %s\n", msg);

      close(pipe_rev[READ]);
      write(pipe_rev[WRITE], msg, BUFFER);
      close(pipe_rev[WRITE]);

      exit(0);

   } 
   else 
   {
      close(pipefd[READ]);          /* Close unused read end */
      write(pipefd[WRITE], argv[1], BUFFER);
      close(pipefd[WRITE]);
      printf("Parent sent msg : %s\n", argv[1]);
      
      wait(NULL);                /* Wait for child */

      close(pipe_rev[WRITE]);
      read(pipe_rev[READ], msg, BUFFER);
      close(pipe_rev[READ]);

      printf("Parent received msg : %s\n", msg);

      exit(0);
   }
}

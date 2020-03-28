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

   char wmsg[(BUFFER)];
   

   if (argc != 2) {
       fprintf(stderr, "Usage: %s <string> (String within quotes if white char is there)\n", argv[0]);
       exit(EXIT_FAILURE);
   }

   if (pipe(pipefd) == -1 && pipe(pipe_rev) == -1) {
       perror("pipe");
       exit(EXIT_FAILURE);
   }

   cpid = fork();
   if (cpid == -1) {
       perror("fork");
       exit(EXIT_FAILURE);
   }

   if (cpid > 0) 
   {
    wait(NULL);                /* Wait for child */

      close(pipefd[WRITE]); 
      // wmsg = malloc(BUFFER);
      read(pipefd[READ], wmsg, BUFFER);
      close(pipefd[READ]);

      printf("PAR : %s\n", wmsg);
      exit(0);

   } 
   else 
   {
      close(pipefd[READ]);          /* Close unused read end */
      char msg[] = "Hi There";
      char *ptr = msg;
      write(pipefd[WRITE], ptr, BUFFER);
      close(pipefd[WRITE]);          /* Reader will see EOF */
      

      exit(0);
   }
}

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
   int pipefd[2];
   pid_t cpid;

   int BUFFER = strlen(argv[1]) + 1;
  char msg[BUFFER];
   
   

   if (argc != 3) {
       fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
       exit(EXIT_FAILURE);
   }

   if (pipe(pipefd) == -1) {
       perror("pipe");
       exit(EXIT_FAILURE);
   }
   cpid = fork();
   if (cpid == -1) {
       perror("fork");
       exit(EXIT_FAILURE);
   }

   if (cpid == 0) // Child
   {
      FILE *f = fopen(argv[2], "wb");
      close(pipefd[WRITE]); 
      char tmp_char; int nbytes;
      // printf("Here is file\n");
      while ((nbytes = read(pipefd[READ], &tmp_char, 1)) != EOF) 
      {
        if (nbytes == 0)
            break;
        fputc(tmp_char, f);
      }
      close(pipefd[READ]);
      fclose(f);
      exit(0);

   } 
   else //parent
   {
      FILE *f = fopen(argv[1], "rb");
      fseek(f, 0, SEEK_END);
      long fsize = ftell(f);
      fseek(f, 0, SEEK_SET); 

      char *data = malloc(fsize + 1);
      fread(data, 1, fsize, f);
      fclose(f);

      data[fsize] = 0;

      close(pipefd[READ]);          /* Close unused read end */
      write(pipefd[WRITE], data, fsize);
      close(pipefd[WRITE]);          /* Reader will see EOF */
      wait(NULL);                /* Wait for child */
      printf("Finished Copying\n");
      exit(0);
   }
}

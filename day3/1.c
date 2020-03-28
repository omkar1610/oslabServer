#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <string.h> 
#include <stdlib.h> 
  
int main(int argc , char *argv[] ) 
{ 
    if (argc != 2) 
    { 
        printf("USAGE : <file> <number>\n"); 
        exit(0); 
    } 
  
    int n = atoi(argv[1]);

    if ( n <= 0 ) 
    { 
        printf("number entered (%d) <= 0\n", n); 
        exit(0); 
    } 

    pid_t pid=fork(); 
    
    if ( pid<0 ) 
    { 
        printf("fork failed\n"); 
        exit(0); 
    } 
  
    else if ( pid==0 ) 
    { 
        int a = 0, b = 1;
        if(n == 1)
        {
            printf("%d\n",a);
        }
        else if(n == 2)
        {
            printf("%d, %d\n",a ,b);
        }
        else
        {
            printf("%d, %d, ",a ,b);
            int c = a+b;
            n = n - 2;
            while(n)
            {
                printf("%d, ",a+b);

                a = b;
                b = c;
                c = a+b;
                n--;
            }
            printf("\b\b \n"); //To remove the last comma from the output
        }
        exit(0); 
    } 
  
    else
    { 
        wait(NULL); 
        // printf("Done\n"); 
    } 
} 
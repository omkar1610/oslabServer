#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCPU(){
    printf("CPU Information :\n");

    //use linux commands
    system("grep -m1 'cpu cores' /proc/cpuinfo");

    //read from the proc file and use string functions
    FILE *fp;
    fp = fopen("/proc/cpuinfo", "r");

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        if(strstr(line, "cpu MHz")!=NULL)
            printf("%s", line);
    }

    fclose(fp);
}

int main(int argc, char const *argv[])
{
    int choice = 0;

    while (1)
    {
        printf("\nEnter your choice :\n");
        printf("1. CPU Information\n");
        printf("2. Linux Kernel Version\n");
        printf("3. Time Since Last Boot\n");
        printf("4. Average Load on System last 15 mins\n");
        printf("5. Memory Information :\n");
        printf("6. Swap SpaceInformation\n");
        printf("7. Swap Partition Information\n");
        printf("8. CPU time Kernel and User Mode\n");
        printf("9. Number of Context Switches\n");
        printf("10. Number of Interrupts\n");
        printf("11. All Information\n");
        printf("12. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printCPU();
            break;
        
        case 2:
            system("uname -r");
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;

        case 8:
            break;

        case 9:
            break;

        case 10:
            break;

        case 11:
            break;

        case 12:
            exit(0);
            break;

        default:
            printf("Invalid Choice!");
            break;
        }
    }
    
    return 0;
}

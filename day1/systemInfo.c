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
    printf("\n");

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
            system("awk '{print \"Kernel Version = \" $0}' /proc/sys/kernel/osrelease");
            printf("\n");
            break;

        case 3:
            system("echo The time in day:hr:min:sec when the system was last booted = && awk ' {print int($1/86400) \":\"int(($1%86400)/3600) \":\" int((($1%86400)%3600)/60) \":\" int($1%60)}' /proc/uptime");
            printf("\n");
            break;

        case 4:
            system("awk '{print \"Average Load on System last 15 mins = \" $3 }' /proc/loadavg");
            printf("\n");
            break;

        case 5:
            system("echo Memory Information : && awk '/Mem[TF]/ {print $0}' /proc/meminfo");
            printf("\n");
            break;

        case 6:
            system("echo Swap Information : && awk '{if($1 ~ /SwapT/) {tot = $2; print \"Swap Total = \" $2, $3;} else if($1 ~ /SwapF/) {print \"Swap Used = \" tot-$2, $3}}' /proc/meminfo");
            printf("\n");
            break;

        case 7:
            system("echo Swap Partition Information\\(Filename = Size\\): && awk 'NR>1 {print $1 \" = \"$3 ,\"Kb\"}' /proc/swaps");
            printf("\n");
            break;

        case 8:
            system("awk '{if ($1 ~ /cpu$/) print \"CPU time User and Kernel Mode(in USER_HX) = \" $2, $4 }' /proc/stat");
            printf("\n");
            break;

        case 9:
            system("awk '/ctxt/ {print \"Total number of context switches = \" $2 }' /proc/stat");
            printf("\n");
            break;

        case 10:
            system("awk '/intr/ {print \"Total number of Interrupts = \" $2 }' /proc/stat");
            printf("\n");
            break;

        case 11:
            printCPU();
            system("awk '{print \"Kernel Version = \" $0}' /proc/sys/kernel/osrelease");
            printf("\n");
            system("echo The time in day:hr:min:sec when the system was last booted = && awk ' {print int($1/86400) \":\"int(($1%86400)/3600) \":\" int((($1%86400)%3600)/60) \":\" int($1%60)}' /proc/uptime");
            printf("\n");
            system("awk '{print \"Average Load on System last 15 mins = \" $3 }' /proc/loadavg");
            printf("\n");
            system("echo Memory Information : && awk '/Mem[TF]/ {print $0}' /proc/meminfo");
            printf("\n");
            system("echo Swap Information : && awk '{if($1 ~ /SwapT/) {tot = $2; print \"Swap Total = \" $2, $3;} else if($1 ~ /SwapF/) {print \"Swap Used = \" tot-$2, $3}}' /proc/meminfo");
            printf("\n");
            system("echo Swap Partition Information\\(Filename = Size\\): && awk 'NR>1 {print $1 \" = \"$3 ,\"Kb\"}' /proc/swaps");
            printf("\n");
            system("awk '{if ($1 ~ /cpu$/) print \"CPU time User and Kernel Mode(in USER_HX) = \" $2, $4 }' /proc/stat");
            printf("\n");
            system("awk '/ctxt/ {print \"Total number of context switches = \" $2 }' /proc/stat");
            printf("\n");
            system("awk '/intr/ {print \"Total number of Interrupts = \" $2 }' /proc/stat");
            printf("\n");
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

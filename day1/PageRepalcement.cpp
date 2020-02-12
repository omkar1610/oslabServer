#include "fifo.h"
#include "lru.h"
#include "lfu.h"
#include <stdio.h>


void FIFO(const char *input)
{
    
    FILE *fp = fopen(input, "r");

    int x, y, tot_frame;
    fscanf(fp, "%d", &x);fscanf(fp, "%d", &tot_frame);

    fifo LL(tot_frame);
    
    while(x--)
    {
        fscanf(fp, "%d", &y);
        LL.FIFO(y);
        //LL.print_list();
    }
    fclose(fp);
    
    cout<<"FIFO Page Faults : "<<LL.page_faults<<endl;
}

void LRU(const char *input)
{
    FILE *fp = fopen(input, "r");

    int x, y, tot_frame;
    fscanf(fp, "%d", &x);fscanf(fp, "%d", &tot_frame);

    lru LL(tot_frame);
    
    while(x--)
    {
        fscanf(fp, "%d", &y);
        LL.LRU(y);
        // LL.print_list();
    }
    fclose(fp);
    
    cout<<"LRU Page Faults : "<<LL.page_faults<<endl;
}

void LFU(const char *input)
{
    FILE *fp = fopen(input, "r");

    int x, y, tot_frame;
    fscanf(fp, "%d", &x);fscanf(fp, "%d", &tot_frame);

    lfu LL(tot_frame);
    
    while(x--)
    {
        fscanf(fp, "%d", &y);
        LL.add_page_node(y);
        // LL.show();
    }
    fclose(fp);
    cout<<"LFU Page Faults : "<<LL.page_faults<<endl;

}

void run_algo(const char *command, const char *input)
{
    if(command[0] == 'F' && command[1] == 'F')
        FIFO(input);
    else if(command[0] == 'L' && command[1] == 'F')
        LFU(input);
    else if(command[0] == 'L' && command[1] == 'R')
        LRU(input);
}

int main(int argc, char const *argv[])
{
    if(argc >5 || argc <2)
        { cout<<"Invalid Input"<<endl; exit(0);}
    else if(argc == 2)
    {
        FIFO(argv[1]);
        LRU(argv[1]);
        LFU(argv[1]);
    }
    else
    {
        for(int i = 2;i<argc;i++)
            run_algo(argv[i], argv[1]);
    }

}
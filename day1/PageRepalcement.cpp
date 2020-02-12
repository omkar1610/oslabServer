#include "fifo.h"
#include "lru.h"
#include "lfu.h"



void FIFO()
{
    fifo LL;
    int x;
    do
    {
        cin>>x;
        LL.FIFO(x);
        LL.print_list();
    }while(x != -1);
    cout<<LL.page_faults<<endl;
}

void LRU()
{
    lru LL;
    int x;
    do
    {
        cin>>x;
        LL.LRU(x);
        LL.print_list();
    }while(x != -1);
    cout<<LL.page_faults<<endl;
}

void LFU()
{
    lfu LL;
    LL.show();
    int x;
    do
    {
        cin>>x;
        //LL.LFU(x);
        LL.add_page_node(x);
        LL.show();
    }while(x != -1);
}


int main()
{
	
}
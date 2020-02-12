#include <iostream>
#include <unordered_map>
using namespace std;


struct node
{
    int page;
    node *up, *down;
    freq_list_node *parent;
};

struct freq_list_node
{
    int freq;
    freq_list_node *next, *prev;
    node *node_list;

};

class lfu
{
private:
    freq_list_node *head;
    // int tot_frames, curr_frames;
    unordered_map<int, node*> page_to_node;

public:
    lfu(){
        head = NULL;
    }

    void LFU(int x){
        /*1. Check if the page is in the memory or node_list

        2. If presernt,
            3.Find its freq and check if freq+1 node is there
                4. if freq+1 is not present create freq+1,
            5.remove and add to freq+1
        6.else create new page node
        6.Check lowest freq and delete the first node and remove from map
        7.check if freq 1 is not present create freq 1 node
        8. add to freq 1 and map as well

        */
    }

    
};

int main()
{
	

	cout<<"Hello"<<endl;
	lfu LL;
    while(1)
    {
    	int x;cin>>x;
    	
    }

    return 0;
}
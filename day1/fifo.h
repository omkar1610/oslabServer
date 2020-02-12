#include <iostream>
#include <unordered_map>
using namespace std;


#ifndef FIFO_H
#define FIFO_H

struct node
{
    int data;
    node *next, *prev;
};

class fifo
{
private:
    node *head,*tail;
    int tot_frames, curr_frames;
    
    
public:
    int page_faults;
	unordered_map<int, node*> nodelist;

    fifo(int tot)
    {
        page_faults = 0;
        head = tail = NULL;
        curr_frames = 0;
        tot_frames = tot;
    }
    void FIFO(int x)
    {
		
    	if(check_key(x) != 1)
    	{
            page_faults++;
    		if(curr_frames == tot_frames)
    		{
    			remove_page();
    			add_node(x);
    		}
    		else
    		{
    			add_node(x);
    		}
    	}
    }

    void print_list()
    {
    	node *tmp = head;
    	while(tmp != NULL)
    	{
    		cout<<tmp->data<<" ";
    		tmp = tmp->next;
    	}
    	cout<<endl;
    }
    void add_node(int x)
    {
        node *tmp = new node;
        tmp->data = x;
        tmp->next = NULL;

        nodelist[x] = tmp; //add to the hash map for direct acess for fifo
        curr_frames++;
        page_faults++;
        // cout<<page_faults<<endl;

        if(head == NULL)
            head = tail = tmp;
        else
        {
            tail->next = tmp;
            tmp->prev = tail;
            tail = tail->next;
        }
    }

    void remove_page()
    {
    	curr_frames--;
    	nodelist.erase(head->data);
    	head = head->next;
    	free(head->prev);
    }

    int check_key(int x) 
	{ 
	    if (nodelist.find(x) == nodelist.end()) 
	        return 0; 
	  
	    return 1; 
	} 
	node *get_node(int x)
	{
		if(check_key(x)==1)
			return nodelist.at(x);
		else return NULL;
	}
};



#endif
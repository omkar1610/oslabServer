#include <iostream>
#include <unordered_map>
using namespace std;




struct node
{
    int data;
    node *next, *prev;
};

class ll
{
private:
    node *head,*tail;
    int tot_frames, curr_frames;
    
public:
	unordered_map<int, node*> nodelist;

    ll()
    {
        head = tail = NULL;
        curr_frames = 0;
        tot_frames = 3;
    }
    void LRU(int x)
    {
		/*

		1. Get the page number
		2. Check if the string is in the list or not, If present Move to last
		3. If not present, if frames are full then remove the head(LRU) and add page to the end of list(MRU)
		other wise just add tot he last


		*/
    	if(check_key(x) == 1)
    	{
    		move_to_last(get_node(x));
    	}
    	else
    	{
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
        nodelist[x] = tmp; //add to the hash map for direct acess for lru
        curr_frames++;

        if(head == NULL)
            head = tail = tmp;
        else
        {
            tail->next = tmp;
            tmp->prev = tail;
            tail = tail->next;
        }
    }
    void move_to_last(node *page)
    {
    	if(page == NULL)
    	{
    		cout<<"Invalid"<<endl;
    	}
    	else if(page == tail)
    	{
    		;
    	}
    	else if(page == head)
    	{
    		head = head->next;
    		tail->next = page;
    		page->prev = tail;
    		page->next = NULL;
    		tail = page;
    	}
    	else
    	{
    		node *before = page->prev;
    		node *after = page->next;

    		before->next = after;
    		after->prev = before;

    		tail->next = page;
    		page->prev = tail;
    		page->next = NULL;
    		tail = page;
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

int main()
{
	

	cout<<"Hello"<<endl;
	ll a;
    while(1)
    {
    	int x;cin>>x;
    	a.LRU(x);

    a.print_list();
    }

    return 0;
}
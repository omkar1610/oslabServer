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
    
public:
	unordered_map<int, node*> nodelist;

    ll(){
        head = tail = NULL;
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
    	head = head->next;
    	free(head->prev);
    }

    int check_key(int key) 
	{ 
	    if (nodelist.find(key) == nodelist.end()) 
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
    a.add_node(1);
    a.add_node(2);
    a.add_node(5);
    a.add_node(12);
    a.add_node(43);
    a.add_node(54);
    a.add_node(8);
    a.add_node(21);
    a.print_list();
    a.move_to_last(a.get_node(1));
    a.print_list();
    cout<<a.get_node(1)->data;
    while(1){
    	int x;cin>>x;
    	a.move_to_last(a.get_node(x));

    a.print_list();
    }
    return 0;
}
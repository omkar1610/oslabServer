//Reference : http://dhruvbird.com/lfu.pdf

#include <iostream>
#include <unordered_map>
using namespace std;


#ifndef LFU_H
#define LFU_H

struct freq_node;
struct page_node;

struct page_node
{
    int page;
    page_node *next, *prev;
    freq_node *parent;
};

struct freq_node
{
    int freq;
    freq_node *next, *prev;
    page_node *head, *tail;

};

class lfu
{
private:
    freq_node *freq_head;
    int tot_frames, curr_frames;
    unordered_map<int, page_node*> page_to_node;

public:
    int page_faults;
    lfu(int tot)
    {
        freq_head = NULL;
        tot_frames = tot;
        curr_frames = 0;
        page_faults = 0;
    }

    int check_key(int x) 
    { 
        if (page_to_node.find(x) == page_to_node.end()) 
            return 0; 
      
        return 1; 
    } 
    
    page_node *get_node(int x)
    {
        if(check_key(x)==1)
            return page_to_node.at(x);
        else return NULL;
    }
    
    void show()
    {
        if(freq_head == NULL)
        {
            printf("Empty\n");
            return;
        }
        // printf("curr = %d\n", curr_frames);

        freq_node *tmp = freq_head;
        while(tmp != NULL)
        {
            // p    rintf("%d = ", tmp->freq);

            page_node *n = tmp->head;
            while(n != NULL)
            {
                printf("%d(%d) ", n->page, n->parent->freq);
                n = n->next;
            }

            // printf(" Reverse : ");
            // n = tmp->tail;
            // while(n != NULL)
            // {
            //     printf("%d(%d) ", n->page, n->parent->freq);
            //     n = n->prev;
            // }

            printf("\n");
            tmp = tmp->next;
        }
        printf("\n");
    }


    void remove_lfu() //conveniently Assumes at least 2 pages must be present before replacement
    //          So that we dont have to check for single freq node deletion
    {
        freq_node *tmp = freq_head;
        page_node *page = tmp->tail; //This is to be deleted
        
        // cout<<"Removing"<<page->page<<endl;

        if(tmp->head == tmp->tail) // Single Node, Then remove freq node
        {
            page_to_node.erase(page->page);
            curr_frames--;
            free(tmp->tail);
            //delete freq node npw
           
            //Since at least 2, so can't be last freq node with 1 page
            if(freq_head == tmp)// first freq_node
            {
                tmp->next->prev = NULL;
                freq_head = tmp->next;
                free(tmp);
            }
            else
            {
                tmp->next->prev = tmp->prev;
                tmp->prev->next = tmp->next;
                free(tmp);
            }

        }
        else    //delete the tail<node
        {
            page_to_node.erase(page->page);
            curr_frames--;
            page->prev->next = NULL;
            tmp->tail = page->prev;
            free(page);
        }

    }

    void add_page_node(int x)
    {
        //====================================================================================================
        //<NOT IN MEMORY
        //====================================================================================================

        if(check_key(x) != 1)    // Not in the memory
        {
            if(curr_frames>=tot_frames) //Remove appropriate page before inserting
            {
                remove_lfu();
            }
            //Get a node for new node
            page_node *page = new page_node;
            page->page = x;
            page->next = page->prev = NULL;

            //Store to hashMAp
            page_to_node[x] = page;
            curr_frames++;
            page_faults++;
            //====================================================================================================
            //EMPTY FREQ LIST => ADD 1ST PAGE
            //====================================================================================================
            if(freq_head == NULL) // 1st page to be added
            {
                freq_node *tmp = new freq_node;
                tmp->freq = 1;

                tmp->head = tmp->tail = page;
                page->parent = tmp;
                
                tmp->next = tmp->prev = NULL;

                freq_head = tmp;
            }
            //====================================================================================================
            // NO FREQ NODE of FREQ = 1  => CREATE FREQ NODE AND ADD PAGE
            //====================================================================================================

            else if(freq_head->freq != 1) // No 1 freq page is present, Create 1 freq and add page to it
            {
                freq_node *tmp = new freq_node;
                tmp->freq = 1;

                tmp->head = tmp->tail = page;
                page->parent = tmp;

                tmp->prev = NULL;
                tmp->next = freq_head;
                freq_head->prev = tmp;

                freq_head = tmp;
            }
            //====================================================================================================
            // FREQ 1 FREQ NODE Present => APPEND THE NEW PAGE
            //====================================================================================================

            else // 1 freq nodelist is there and non empty,  so add to the existing nodelist
            {
                freq_node *par = freq_head;
                
                page->next = par->head;
                par->head->prev = page;
                page->parent = par;
                par->head = page;
            }
        }
        //====================================================================================================
        // Page IN MEMORY
        //====================================================================================================

        else // Present in the memory
        {
            // Get details of the PAGE node

            page_node *page = get_node(x);
            freq_node *par = page->parent;
            int page_freq = par->freq;
            
            {
                //====================================================================================================
                // TAIL FREQ NODE > ONE NODE > FREQ++(No need to create a new Freq Node)
                //====================================================================================================
                if(par->next == NULL) // last freq node
                {
                    // cout<<"here";
                    if(par->head == par->tail) // Only one node, Just increase 
                                                // node freq directly
                    {
                        par->freq++;
                    }
                    //====================================================================================================
                    // TAIL FREQ NODE > NO FREQ +1 Node > REMOVE from parent, CREATE freq + 1 ADD MOVE the 1ST PAGE
                    //====================================================================================================

                    else    
                    {
                        if(par->head == par->tail) // if single node then freq++ and done
                        {
                            par->freq++;
                        }
                        else 
                        {
                            //remove and create new freq node and add to the list
                            //Remove from par freq node
                            if(par->head == page)//if the head node
                            {
                                par->head = page->next;
                                page->next->prev = NULL;
                            }
                            else if(par->tail == page) // if the tail node
                            {
                                page->prev->next = NULL;
                                par->tail = page->prev;
                            }
                            else // Middle node
                            {
                                page->prev->next = page->next;
                                page->next->prev = page->prev;
                            }

                            //add to new freq node
                            freq_node *tmp = new freq_node;
                            tmp->freq = page_freq + 1;

                            tmp->head = tmp->tail = page;

                            page->next = page->prev = NULL;
                            page->parent = tmp;

                            tmp->prev = par;
                            tmp->next = NULL;
                            
                            par->next = tmp;
                        }

                    }
                }
                //====================================================================================================
                // NON LAST. FREQ+1 AVAILABLE > REMOVE and APPEND
                //====================================================================================================

                else // Non-last node in freq list 
                {
                    if(par->next->freq == par->freq + 1)// freq + 1 is available
                        // Just remove from par and add par->next
                    {
                        //Remove from par freq node
                        //if single node then remove the freq_node as well
                        if(par->head == par->tail)
                        {
                            freq_node *tmp = par->next;
                            if(freq_head == par)// first freq_node
                            {
                                par->next->prev = NULL;
                                freq_head = par->next;
                                free(par);
                            }
                            else
                            {
                                par->next->prev = par->prev;
                                par->prev->next = par->next;
                                free(par);
                            }

                            tmp->head->prev = page;
                            page->next = tmp->head;
                            tmp->head = page;

                            page->prev = NULL;
                            page->parent = tmp;
                            tmp->head = page;
                        }
                        else 
                        {
                            //Remove from par freq node
                            if(par->head == page)//if the head node
                            {
                                par->head = page->next;
                                page->next->prev = NULL;
                            }
                            else if(par->tail == page) // if the tail node
                            {
                                page->prev->next = NULL;
                                par->tail = page->prev;
                            }
                            else // Middle node
                            {
                                page->prev->next = page->next;
                                page->next->prev = page->prev;
                            }
                            
                            //add to freq + 1 ie par->next
                            freq_node *tmp = par->next;

                             
                            tmp->head->prev = page;
                            page->next = tmp->head;

                            page->prev = NULL;
                            page->parent = tmp;
                            tmp->head = page;
                        }

                    }
                    //====================================================================================================
                    // NO FREQ + 1 > REMOVE CREATE ADD 1ST PAGE
                    //====================================================================================================

                    else 
                    {
                        if(par->head == par->tail) // if single node then freq++ and done
                        {
                            par->freq++;
                        }
                        else // create a new freq node for freq+1 and add to this
                        {

                            //Remove from par freq node
                            if(par->head == page)//if the head node
                            {
                                par->head = page->next;
                                page->next->prev = NULL;
                            }
                            else if(par->tail == page) // if the tail node
                            {
                                page->prev->next = NULL;
                                par->tail = page->prev;
                            }
                            else // Middle node
                            {
                                page->prev->next = page->next;
                                page->next->prev = page->prev;
                            }

                            freq_node *tmp = new freq_node;
                            tmp->freq = page_freq + 1;

                            tmp->next = par->next;
                            tmp->next->prev = tmp;

                            tmp->prev = par;
                            par->next = tmp;

                            tmp->head = tmp->tail = page;
                            page->parent = tmp;
                            page->next = page->prev = NULL;
                        }

                        
                    }
                }
            }
        }
    }

};

#endif
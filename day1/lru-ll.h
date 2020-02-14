#include <stdio.h>
#include <stdlib.h>

#define TOT_ELE ll->tot_ele
#define NUM_ELE ll->num_ele
#define HEAD ll->head
#define TAIL ll->tail
#define FREE ll->free
#define ELEMENT ll->elements

#define getdata(x) ll->elements[(x)].data
#define getnext(x) ll->elements[(x)].next
#define getprev(x) ll->elements[(x)].prev

#define DATA int

typedef struct
{
	DATA data;
	int next, prev;
}NODE;

typedef struct
{
	int tot_ele, num_ele;
	int head, tail, free;
	NODE *elements;
}LL;
void init(LL *ll, int tot_ele)
{
	TOT_ELE = tot_ele;	NUM_ELE = 0;
	HEAD = TAIL = -1, FREE = 0;

	ELEMENT = malloc(TOT_ELE * sizeof(NODE));//calloc(TOT_ELE , sizeof(NODE));

	//Set link of free elements
	for(int i=0 ; i<TOT_ELE-1 ; i++)
		getnext(i) = i+1, getprev(i) = -1;
	getnext(TOT_ELE-1) = -1;
}

void showComplete(LL *ll)
{
	printf("\nDATA\n");
	for(int i=0, h = HEAD; i<NUM_ELE ; i++ , h = getnext(h))
			printf("%d %d %d\n",getdata(h), getnext(h), getprev(h));

	printf("FREE : ");
	for(int free = FREE; free != -1; free = getnext(free)) 
		printf("%d ",free);
	printf("\n");

	printf("\n");
}
int search(LL *ll, DATA key) //retuns loc or -1
{
	int head = HEAD;
	int num_ele = NUM_ELE;
	while(num_ele--)
	{
		if(key == getdata(head))
			return head;
		head = getnext(head);
	}
	return -1;	
}

void remove_lru(LL *ll)
{
	int old = HEAD;
	HEAD = getnext(HEAD);

	getnext(old) = FREE;
	FREE = old;
	NUM_ELE --;
}

void insert(LL *ll, DATA x)
{
	if( NUM_ELE == TOT_ELE)
		remove_lru(ll);
	

	if(NUM_ELE != 0 && NUM_ELE < TOT_ELE)
	{
		NUM_ELE ++;
		getdata(FREE) = x;
		getprev(FREE) = TAIL;
		
		getnext(TAIL) = FREE;
		TAIL = FREE;
		// getnext(TAIL) = -1;

		FREE = getnext(FREE);

	}
	else if(NUM_ELE == 0)
	{
		NUM_ELE ++;
		getdata(FREE) = x;
		getprev(FREE) = TAIL;

		HEAD = TAIL = FREE;
		// getnext(TAIL) = -1;
		FREE = getnext(FREE);
	}
	else
		printf("Full\n");
}

void move_last(LL *ll, int loc) //search and move to last of list
{
	// int loc = search(ll, key);
	if(loc != -1 && TAIL != loc)
	{
		if(HEAD == loc)
		{
			HEAD = getnext(loc);
		}
		int prev = getprev(loc);
		int next = getnext(loc);

		getnext(prev) = next;
		getprev(next) = prev;
		
		getnext(TAIL) = loc;
		getprev(loc) = TAIL;
		TAIL = loc;
	}
}


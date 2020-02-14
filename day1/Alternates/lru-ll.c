#include "lru-ll.h"


void lru(LL *ll, int page)
{
	int loc = search(&ll, page);
	if(loc == 1)
		move_last(&ll, loc);
	else
		insert(&ll, page);
}

int main()
{
	LL ll;
	int tot_ele = 5;
	
	init(&ll, tot_ele);
	
}
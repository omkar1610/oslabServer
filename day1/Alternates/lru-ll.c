#include "lru-ll.h"



int main()
{
	FILE *fp = fopen("input", "r");
    int x, p,max_frames;


	fscanf(fp, "%d", &x);
	fscanf(fp, "%d", &max_frames);
	
	LL ll;
	init(&ll, max_frames);
	//For each page
	int page_fault = 0;
	while(x--)
    {
    	fscanf(fp, "%d", &p);
    	
    	//LRU
		int loc = search(&ll, p);
		if(loc == 1)
			move_last(&ll, loc);
		else
			page_fault++, insert(&ll, p);

		// showComplete(&ll);
	}

	fclose(fp);
	printf("PF %d\n", page_fault);
	
}
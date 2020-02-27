#include <stdio.h>
#include <stdlib.h>
int find_min(int *arr)
{
	int min = 99999, loc = 0;
	for(int i = 1; i<arr[0]; i++)
		if(arr[i] != 0 && arr[i]<min)
			min = arr[i], loc = i;
	return loc;
}
void print_arr(int *arr)
{
	for(int i = 0; i<=arr[0]; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
	FILE *fp = fopen("input", "r");
    int x, p, *arr;
    arr = malloc(sizeof(int));
	int curr_frames = 0, max_frames;
	arr[0] = 0;

	fscanf(fp, "%d", &x);
	fscanf(fp, "%d", &max_frames);
	//For each page

	while(x--)
    {
    	fscanf(fp, "%d", &p);
    	print_arr(arr);
    	// printf(": %d\n", p);
        
        
		if(arr[0] < p)
		{
			if(curr_frames == max_frames)
			{
				arr[find_min(arr)] = 0;
				curr_frames--;
			}

			arr = (int *)realloc(arr, (p+1) *sizeof(int));
			for(int i = arr[0]+1;i<p;i++)
				arr[i] = 0;
			arr[p] = 1;
			arr[0] = p;
			curr_frames++;
			
		}
		else
		{
			if(arr[p] != 0)
				arr[p]++;
			else
			{
				if(curr_frames == max_frames)
				{
					arr[find_min(arr)] = 0;
					curr_frames--;
				}

				arr[p] = 1;
				curr_frames++;
			}

		}
		
	}
	print_arr(arr);
    fclose(fp);
}
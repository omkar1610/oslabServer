#include "ansuman.h"

#define get_offset(x) (x) & OFFSET_MASK
#define get_logical(x) (x>>8) & PAGE_MASK



int main (int argc, const char *argv[])
{

    printf("%lu %lu\n", sizeof(int), sizeof(char));
    int logical_address, logical_page, logical_offset, physical_frame, physical_offset;
    scanf("%d",&logical_address);

    
    logical_offset = get_offset(logical_address);
    logical_address = get_logical(logical_address);
    logical_page = logical_address;
    printf("lA = %d | %d\n", logical_page, logical_offset);

    //Initialize Page Table
    for (int i = 0; i < PAGES; ++i)
        pagetable[i] = -1;

    // Find if the page is there in the page table or not

    if(pagetable[logical_page] == -1)
    {
        printf("Page is not yet in the table\n");
    }
    else
    {
        printf("Page is present in the table\n");
        physical_frame = pagetable[logical_page];
        physical_offset = logical_offset;
        printf("PA %d | %d\n", physical_frame, physical_offset);

    }

    FILE *fp = fopen("BACKING_STORE.bin", "rb");

    char buff[256];
    int bytes_read = fread(buff, 1, 256, fp);
    printf("Bytes read = %d\n", bytes_read);
    for (int i = 0; i < 256; ++i)
    {
        printf("%d", buff[i]);
    }


    fclose(fp);



    // if (argc != 3) {
    //     fprintf(stderr, "Usage ./a.out backingstore input\n");
    //     exit(1);
    // }

    // const char *backing_filename = argv[1]; 
    // int backing_fd = open(backing_filename, O_RDONLY);
    // backing = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0); 

    // const char *input_filename = argv[2];
    // FILE *input_fp = fopen(input_filename, "r");

    // // Fill page table entries with -1 for initially empty table.
    
    // // fill in the necessary code here

    // // Character buffer for reading lines of input file.
    // char buffer[BUFFER_SIZE];

    // // Data we need to keep track of to compute stats at end.
    // int total_addresses = 0;
    // int tlb_hits = 0;
    // int page_faults = 0;

    // // Number of the next unallocated physical page in main memory
    // unsigned char free_page = 0;

    // while (fgets(buffer, BUFFER_SIZE, input_fp) != NULL) {
        
    //     //fill in the code here
    //     //your code
        
    //     total_addresses++;
        
    //     int logical_address;
    //     int offset;
    //     int logical_page;
        
        
    //     //complete the code by filling in the following functionality
    //     //logical_address = 
    //     //offset = 
    //     //logical_page = 

    //     int physical_page = search_tlb(logical_page);

    //     // TLB hit
    //     if (physical_page != -1) {
    //         //fill in the necessary code here
    //     } 
    //     else { // TLB miss
    //         //fill in the necessary code here
    //         //your code
            
    //         // Page fault
    //         if (physical_page == -1) {
                
    //             //fill in the necessary code here
    //             //your code


    //             // Copy page from backing file into physical memory
                
    //             //fill in the necessary code here
    //             //your code
                
    //         }

    //         add_to_tlb(logical_page, physical_page);
    //     }

    //     int physical_address = (physical_page << OFFSET_BITS) | offset;
    //     signed char value = main_memory[physical_page * PAGE_SIZE + offset];

    //     printf("Virtual address: %d Physical address: %d Value: %d\n", logical_address, physical_address, value);
    // }

    // printf("Number of Translated Addresses = %d\n", total_addresses);
    // printf("Page Faults = %d\n", page_faults);
    // printf("Page Fault Rate = %.3f\n", page_faults / (1. * total_addresses));
    // printf("TLB Hits = %d\n", tlb_hits);
    // printf("TLB Hit Rate = %.3f\n", tlb_hits / (1. * total_addresses));

    return 0;
}

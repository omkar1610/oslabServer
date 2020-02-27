#include <iostream>
using namespace std;

#define TLB_SIZE 16
#define PAGE_TABLE_SIZE 28
#define PAGES 256
#define PAGE_MASK 255

#define PAGE_SIZE 256
#define OFFSET_BITS 8
#define OFFSET_MASK 255

#define MEMORY_SIZE PAGES * PAGE_SIZE

// Max number of characters per line of input file to read.
#define BUFFER_SIZE 10

struct tlbentry {
    unsigned char logical;
    unsigned char physical;
};

class project
{
private:

public:
	int LA_Mask(int la)
	{}

};
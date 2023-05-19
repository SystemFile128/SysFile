#include<stdio.h>
#include<math.h>

#define PAGE_SIZE 256
#define PAGE_TABLE_SIZE 256
#define FRAME_SIZE 256
#define FRAME_TABLE_SIZE 256
#define MEMORY_SIZE (FRAME_SIZE * FRAME_TABLE_SIZE)

// A page table entry stores the frame number and a validity bit.
typedef struct page_table_entry {
    int frame_number;
    int valid;
} PageTableEntry;

// A frame table entry stores the page number and a reference bit.
typedef struct frame_table_entry {
    int page_number;
    int referenced;
} FrameTableEntry;

int main() {
    // Initialize the page table and frame table.
    PageTableEntry page_table[PAGE_TABLE_SIZE];
    FrameTableEntry frame_table[FRAME_TABLE_SIZE];
    int i;
    for (i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].valid = 0;
    }
    for (i = 0; i < FRAME_TABLE_SIZE; i++) {
        frame_table[i].referenced = 0;
    }

    // Read the logical address from the user.
    int logical_address;
    printf("Enter a logical address: ");
    scanf("%d", &logical_address);

    // Calculate the page number and offset from the logical address.
    int page_number = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;

    // Check if the page is in memory.
    if (page_table[page_number].valid == 0) {
        // Page fault: the page is not in memory.
        // Find a free frame in the frame table.
        int frame_number = -1;
        for (i = 0; i < FRAME_TABLE_SIZE; i++) {
            if (frame_table[i].page_number == -1) {
                frame_number = i;
                break;
            }
        }
        if (frame_number == -1) {
            // No free frame: use a replacement algorithm (e.g., LRU or FIFO).
            // For simplicity, we'll just use the first frame as the victim.
            frame_number = 0;
            // Invalidate the page table entry for the victim frame.
            page_table[frame_table[frame_number].page_number].valid = 0;
        }
        // Update the page table and frame table.
        page_table[page_number].frame_number = frame_number;
        page_table[page_number].valid = 1;
        frame_table[frame_number].page_number = page_number;
        frame_table[frame_number].referenced = 1;
    }

    // Calculate the physical address from the page table and offset.
    int physical_address = page_table[page_number].frame_number * FRAME_SIZE + offset;

    printf("Physical address: %d\n", physical_address);

    return 0;
}
/*page_number = logical_address / PAGE_SIZE;
page_number = 6421 / 256;
page_number = 25;
offset = logical_address % PAGE_SIZE;
offset = 6421 % 256;
offset = 21;
*/
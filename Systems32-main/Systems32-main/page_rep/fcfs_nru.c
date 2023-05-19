#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3

// Structure to represent a page
typedef struct {
    int pageNumber;
    int referenceBit;
} Page;

// Function to display the page table
void displayPageTable(Page pageTable[], int size) {
    printf("Page Table: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", pageTable[i].pageNumber);
    }
    printf("\n");
}

// Function to find the index of the oldest page in the page table
int findOldestPage(Page pageTable[], int size) {
    int oldestPageIndex = 0;
    int oldestPageAge = pageTable[0].referenceBit;

    for (int i = 1; i < size; i++) {
        if (pageTable[i].referenceBit < oldestPageAge) {
            oldestPageIndex = i;
            oldestPageAge = pageTable[i].referenceBit;
        }
    }

    return oldestPageIndex;
}

// Function to implement the First Come First Serve (FCFS) page replacement algorithm
void firstComeFirstServe(int pageReferences[], int numReferences) {
    printf("First Come First Serve (FCFS):\n");

    Page pageTable[FRAME_SIZE] = {0};
    int pageFaults = 0;

    for (int i = 0; i < numReferences; i++) {
        int currentPage = pageReferences[i];
        int pageFound = 0;

        // Check if the page is already present in the page table
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (pageTable[j].pageNumber == currentPage) {
                pageFound = 1;
                break;
            }
        }

        // If the page is not found, replace the oldest page with the current page
        if (!pageFound) {
            pageTable[pageFaults % FRAME_SIZE].pageNumber = currentPage;
            pageFaults++;
        }

        displayPageTable(pageTable, FRAME_SIZE);
    }

    printf("Total page faults: %d\n\n", pageFaults);
}

// Function to implement the Not Recently Used (NRU) page replacement algorithm
void notRecentlyUsed(int pageReferences[], int numReferences) {
    printf("Not Recently Used (NRU):\n");

    Page pageTable[FRAME_SIZE] = {0};
    int pageFaults = 0;
    int referenceCounter = 0;

    for (int i = 0; i < numReferences; i++) {
        int currentPage = pageReferences[i];
        int pageFound = 0;

        // Check if the page is already present in the page table
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (pageTable[j].pageNumber == currentPage) {
                pageFound = 1;
                pageTable[j].referenceBit = referenceCounter++;
                break;
            }
        }

        // If the page is not found, replace the page with the lowest reference bit
        if (!pageFound) {
            int oldestPageIndex = findOldestPage(pageTable, FRAME_SIZE);
            pageTable[oldestPageIndex].pageNumber = currentPage;
            pageTable[oldestPageIndex].referenceBit = referenceCounter++;
            pageFaults++;
        }

        // Reset reference bits every 3 page references
        if (referenceCounter == 3 * FRAME_SIZE) {
            for (int j = 0; j < FRAME_SIZE; j++) {
                pageTable[j].referenceBit = 0;
            }
            referenceCounter = 0;
        }

        displayPageTable(pageTable, FRAME_SIZE);
    }

    printf("Total page faults: %d\n\n", pageFaults);
}

int main() {
    int pageReferences[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};
    int numReferences = sizeof(pageReferences) / sizeof(pageReferences[0]);

    firstComeFirstServe(pageReferences, numReferences);
    notRecentlyUsed(pageReferences, numReferences);

    return 0;
}

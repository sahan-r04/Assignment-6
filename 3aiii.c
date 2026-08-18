/*
 * Exercise VI - Question 2(b)
 * Same memory allocator as 2a.c, extended with a Defragment() function
 * that repacks every allocated block so that all used blocks become
 * contiguous (all the free space is pushed to the end of the array).
 *
 * Note: in a real allocator this would invalidate any pointers the caller
 * is still holding, since blocks move to new indices. This is flagged
 * with a comment where it happens - it is fine for this simulation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_SIZE 200

int memory[MEM_SIZE];
int allocated[MEM_SIZE];
int nextId = 1;

void *NewMalloc(int dataType) {
    int needed = dataType;
    int start = -1, count = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        if (allocated[i] == 0) {
            if (count == 0) start = i;
            count++;
            if (count == needed) {
                for (int j = start; j < start + needed; j++)
                    allocated[j] = nextId;
                nextId++;
                return (void *)&memory[start];
            }
        } else {
            count = 0;
        }
    }
    printf("NewMalloc: not enough contiguous memory for %d blocks.\n", needed);
    return NULL;
}

void NewFree(void *ptr) {
    if (ptr == NULL) return;
    int index = (int *)ptr - memory;
    if (index < 0 || index >= MEM_SIZE) {
        printf("NewFree: invalid pointer.\n");
        return;
    }
    int id = allocated[index];
    if (id == 0) {
        printf("NewFree: memory at this pointer is already free.\n");
        return;
    }
    for (int i = 0; i < MEM_SIZE; i++)
        if (allocated[i] == id) allocated[i] = 0;
}

void printMemoryMap(void) {
    for (int i = 0; i < MEM_SIZE; i++)
        printf("%c", allocated[i] == 0 ? '.' : '#');
    printf("\n");
}

/* Repacks all allocated blocks to the front of the array, in the order
 * they currently appear, leaving all free space contiguous at the end.
 * Pointers obtained before defragmenting are no longer valid afterwards. */
void Defragment(void) {
    int tempMem[MEM_SIZE];
    int tempAlloc[MEM_SIZE];
    int idx = 0;

    for (int i = 0; i < MEM_SIZE; i++) {
        if (allocated[i] != 0) {
            tempMem[idx] = memory[i];
            tempAlloc[idx] = allocated[i];
            idx++;
        }
    }
    for (int i = idx; i < MEM_SIZE; i++) {
        tempMem[i] = 0;
        tempAlloc[i] = 0;
    }

    memcpy(memory, tempMem, sizeof(memory));
    memcpy(allocated, tempAlloc, sizeof(allocated));

    printf("Defragment: memory repacked, %d blocks now contiguous from index 0.\n", idx);
}

int main(void) {
    /* create fragmentation: allocate 3 variables, free the middle one */
    void *pA = NewMalloc(sizeof(int));     /* 4 blocks */
    void *pB = NewMalloc(sizeof(double));  /* 8 blocks */
    void *pC = NewMalloc(sizeof(char));    /* 1 block  */

    printf("Before freeing pB (fragment in the middle):\n");
    printMemoryMap();

    NewFree(pB);
    printf("\nAfter freeing pB, a hole appears in the middle:\n");
    printMemoryMap();

    Defragment();
    printf("\nAfter Defragment(), all used blocks are packed together:\n");
    printMemoryMap();

    /* silence unused variable warnings for pA / pC, kept only for the demo */
    (void)pA;
    (void)pC;

    return 0;
}

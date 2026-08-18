/*
 * Exercise VI - Question 2(a)
 * Simulates dynamic memory allocation on top of an integer array of 200
 * elements. Each cell of the array is treated as one memory block.
 *
 * NewMalloc(int dataType)  -> dataType is the number of contiguous blocks
 *                             needed (e.g. pass sizeof(int), sizeof(double),
 *                             sizeof(char) ...). Returns a void* to the
 *                             first block assigned, or NULL if there is not
 *                             enough contiguous free space.
 * NewFree(void *ptr)       -> frees all blocks that belong to the
 *                             allocation starting at ptr.
 */

#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 200

int memory[MEM_SIZE];      /* the simulated memory              */
int allocated[MEM_SIZE];   /* 0 = free, otherwise = allocation id */
int nextId = 1;

/* Finds the first contiguous run of free blocks of the requested size */
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

    for (int i = 0; i < MEM_SIZE; i++) {
        if (allocated[i] == id) allocated[i] = 0;
    }
    printf("NewFree: memory freed.\n");
}

int isMemoryFull(void) {
    for (int i = 0; i < MEM_SIZE; i++)
        if (allocated[i] == 0) return 0;
    return 1;
}

void printMemoryMap(void) {
    for (int i = 0; i < MEM_SIZE; i++)
        printf("%c", allocated[i] == 0 ? '.' : '#');
    printf("\n");
}

int main(void) {
    printf("Initial memory map (200 blocks, '.' = free, '#' = used):\n");
    printMemoryMap();

    /* allocate a few variables of different primitive sizes */
    void *pInt    = NewMalloc(sizeof(int));
    void *pDouble = NewMalloc(sizeof(double));
    void *pChar   = NewMalloc(sizeof(char));

    printf("\nAfter allocating an int, a double and a char:\n");
    printMemoryMap();

    printf("\nIs memory full? %s\n", isMemoryFull() ? "Yes" : "No");

    NewFree(pDouble);
    printf("\nAfter freeing the double:\n");
    printMemoryMap();

    NewFree(pInt);
    NewFree(pChar);

    printf("\nAfter freeing everything:\n");
    printMemoryMap();

    return 0;
}

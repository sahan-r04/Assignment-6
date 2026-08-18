#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMSIZE 200

int memory[MEMSIZE];
int used[MEMSIZE];
int nextid = 1;

void *NewMalloc(int type) {
    int needed = type;
    int start = -1, count = 0;

    for (int i = 0; i < MEMSIZE; i++) {
        if (used[i] == 0) {
            if (count == 0) start = i;
            count++;
            if (count == needed) {
                for (int j = start; j < start + needed; j++)
                    used[j] = nextid;
                nextid++;
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
    if (index < 0 || index >= MEMSIZE) {
        printf("NewFree: invalid pointer.\n");
        return;
    }
    int id = used[index];
    if (id == 0) {
        printf("NewFree: memory at this pointer is already free.\n");
        return;
    }
    for (int i = 0; i < MEMSIZE; i++)
        if (used[i] == id) used[i] = 0;
}

void showmap(void) {
    for (int i = 0; i < MEMSIZE; i++)
        printf("%c", used[i] == 0 ? '.' : '#');
    printf("\n");
}

void defrag(void) {
    int temp1[MEMSIZE];
    int temp2[MEMSIZE];
    int count = 0;

    for (int i = 0; i < MEMSIZE; i++) {
        if (used[i] != 0) {
            temp1[count] = memory[i];
            temp2[count] = used[i];
            count++;
        }
    }
    for (int i = count; i < MEMSIZE; i++) {
        temp1[i] = 0;
        temp2[i] = 0;
    }

    memcpy(memory, temp1, sizeof(memory));
    memcpy(used, temp2, sizeof(used));

    printf("defrag: memory repacked, %d blocks now contiguous from index 0.\n", count);
}

int main(void) {
    void *p1 = NewMalloc(sizeof(int));
    void *p2 = NewMalloc(sizeof(double));
    void *p3 = NewMalloc(sizeof(char));

    printf("Before freeing p2 (fragment in the middle):\n");
    showmap();

    NewFree(p2);
    printf("\nAfter freeing p2, a hole appears in the middle:\n");
    showmap();

    defrag();
    printf("\nAfter defrag(), all used blocks are packed together:\n");
    showmap();

    (void)p1;
    (void)p3;

    return 0;
}

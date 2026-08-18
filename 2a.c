#include <stdio.h>
#include <stdlib.h>

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

    for (int i = 0; i < MEMSIZE; i++) {
        if (used[i] == id) used[i] = 0;
    }
    printf("NewFree: memory freed.\n");
}

int isfull(void) {
    for (int i = 0; i < MEMSIZE; i++)
        if (used[i] == 0) return 0;
    return 1;
}

void showmap(void) {
    for (int i = 0; i < MEMSIZE; i++)
        printf("%c", used[i] == 0 ? '.' : '#');
    printf("\n");
}

int main(void) {
    printf("Initial memory map (200 blocks, '.' = free, '#' = used):\n");
    showmap();

    void *p1 = NewMalloc(sizeof(int));
    void *p2 = NewMalloc(sizeof(double));
    void *p3 = NewMalloc(sizeof(char));

    printf("\nAfter allocating an int, a double and a char:\n");
    showmap();

    printf("\nIs memory full? %s\n", isfull() ? "Yes" : "No");

    NewFree(p2);
    printf("\nAfter freeing the double:\n");
    showmap();

    NewFree(p1);
    NewFree(p3);

    printf("\nAfter freeing everything:\n");
    showmap();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMSIZE 200

unsigned char memory[MEMSIZE];
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
    printf("NewMalloc: not enough contiguous memory for %d bytes.\n", needed);
    return NULL;
}

void NewFree(void *ptr) {
    if (ptr == NULL) return;

    int index = (unsigned char *)ptr - memory;
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
    printf("Initial memory map (200 byte-blocks, '.' = free, '#' = used):\n");
    showmap();

    char        *p1 = (char *)NewMalloc(sizeof(char));
    short       *p2 = (short *)NewMalloc(sizeof(short));
    int         *p3 = (int *)NewMalloc(sizeof(int));
    long        *p4 = (long *)NewMalloc(sizeof(long));
    float       *p5 = (float *)NewMalloc(sizeof(float));
    double      *p6 = (double *)NewMalloc(sizeof(double));
    long double *p7 = (long double *)NewMalloc(sizeof(long double));

    *p1 = 'Z';
    *p2 = 123;
    *p3 = 45678;
    *p4 = 9876543L;
    *p5 = 3.14f;
    *p6 = 2.718281828;
    *p7 = 1.6180339887L;

    printf("\nAfter allocating char, short, int, long, float, double, long double:\n");
    showmap();

    printf("\nchar=%c short=%d int=%d long=%ld float=%.2f double=%.6f long double=%.10Lf\n",
           *p1, *p2, *p3, *p4, *p5, *p6, *p7);

    printf("\nIs memory full? %s\n", isfull() ? "Yes" : "No");

    NewFree(p5);
    NewFree(p6);
    NewFree(p7);
    NewFree(p1);
    NewFree(p2);
    NewFree(p3);
    NewFree(p4);

    printf("\nAfter freeing everything:\n");
    showmap();

    return 0;
}

# Exercise VI - C Solutions

SCS 1301 - Data Structures and Program Design Using C

| File       | Question | Description |
|------------|----------|-------------|
| `1.c`      | Q1       | Extends Exercise IV - 3(e)'s scientific calculator menu. All 14 operations are dispatched through a **function pointer table**, plus the division sub-menu, history (option 16), and exit (option 15). |
| `2a.c`     | Q2(a)    | Simulates a 200-block memory allocator: `NewMalloc(int dataType)` and `NewFree(void *ptr)` over an `int[200]` pool. |
| `2b.c`     | Q2(b)    | Extends 2a with `Defragment()`, which repacks all allocated blocks to be contiguous. |
| `2c.c`     | Q2(c)    | Extends the allocator to work with **any primitive type** using a generic `unsigned char[200]` byte pool. |
| `3ai.c`    | Q3(a)(i)   | Euclidean distance between two 2D points. |
| `3aii.c`   | Q3(a)(ii)  | Manhattan distance between two 2D points (sheet's "Mantan Distance" is a typo for Manhattan). |
| `3aiii.c`  | Q3(a)(iii) | Chebyshev distance between two 2D points. |

## Build

Each file is a standalone program. Compile with, e.g.:

```bash
gcc -Wall -o calc 1.c -lm
gcc -Wall -o memalloc 2a.c
gcc -Wall -o dist 3ai.c -lm
```

(`-lm` is needed for files that use `math.h`.)

All files were compiled with `gcc -Wall -Wextra` and run with sample input to confirm they work with no warnings or errors.

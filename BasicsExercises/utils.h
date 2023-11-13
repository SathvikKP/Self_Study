#include <stdio.h>
#include <stdlib.h>



#define MALLOC(p,s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE);\
    }

#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

void printint(int, ...);
void printarray(int[], int);
void printarray_p(int**, int);
void print2Darray(int m, int n, int[m][n]);
void dealloc_warn();
void read_int_from_file(char[], size_t, int**, int*);
void generate_random_int_array(int**, int, int);

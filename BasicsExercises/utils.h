#include <stdio.h>
#include <stdlib.h>



#define MALLOC(p,s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE);\
    }

#define REALLOC(p,s) \
    if (!((p) = realloc(p,s))) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE);\
    }

#define CALLOC(p,n,s) \
    if (!((p) = calloc(n,s))) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE);\
    }


#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

void printint(int, ...);
void printdouble(int num, ...);
void printarray(int[], int);
void printarray_p(int**, int);
void print2Darray(int m, int n, int[m][n]);
void dealloc_warn();
void read_int_from_file(char[], size_t, int**, int*);
void generate_random_int_array(int**, int, int);
int** get_2d_array(int, int);
void print2Darray_p(int**, int, int);
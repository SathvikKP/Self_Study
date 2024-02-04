#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "utils.h"

struct list {
    char data;
    struct list* link;
};

typedef struct list list;

void matrix_populate(int** a, int rows, int cols) {
    int i = 0, j = 0, count = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            *(*(a + i) + j) = ++count;
        }
    }
}


void matrix_add(int** a, int** b, int** c, int rows, int cols) {
    int i = 0, j = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            //c[i][j] = a[i][j] + b[i][j];
            *(*(c + i) + j) = *(*(a + i) + j) + *(*(b + i) + j);
        }
    }
}


void matrix_mult(int** a, int **b, int**c, int rows_a, int cols_a, int rows_b, int cols_b) {
    
    int i = 0, j = 0, k = 0;
    if (cols_a != rows_b) {
        fprintf(stderr,"Error! Matrices cannot be multiplied : cols_a != rows_b");
        exit(EXIT_FAILURE);
    }
    //c = get_2d_array(rows_a, cols_b);
    //i --> rows_a;
    //j --> cols_b;
    //k --> cols_a; (k --> rows_b)

    for (i = 0; i < rows_a; i++) {
        for (j = 0; j < cols_b; j++) {
            for (k = 0; k < cols_a; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}


void matrix_transpose(int** A, int** B, int rows_a, int cols_a) {
    int i = 0, j = 0;
    for (i = 0; i < rows_a; i++) {
        for (j = 0; j < cols_a; j++) {
            B[j][i] = A[i][j];
        }
    }
}


void matrix_driver() {
    
    int** A = NULL; int** B = NULL; int** C = NULL;
    int rows = 3, cols = 4;

    A = get_2d_array(rows, cols); matrix_populate(A, rows, cols); print2Darray_p(A, rows, cols); printf("\n");
    B = get_2d_array(rows, cols); matrix_populate(B, rows, cols); print2Darray_p(B, rows, cols); printf("\n");

    C = get_2d_array(rows, cols);
    matrix_add(A, B, C, rows, cols);
    print2Darray_p(C, rows, cols); printf("\n");

    free2Darray(A, rows, cols); free2Darray(B, rows, cols); free2Darray(C, rows, cols);

    int rows_a = 3, cols_a = 2, rows_b = 2, cols_b = 3; 
    int rows_c = rows_a; int cols_c = cols_b;

    A = get_2d_array(rows_a, cols_a);  matrix_populate(A, rows_a, cols_a); print2Darray_p(A, rows_a, cols_a); printf("\n");
    B = get_2d_array(rows_b, cols_b);  matrix_populate(B, rows_b, cols_b); print2Darray_p(B, rows_b, cols_b); printf("\n");
    C = get_2d_array(rows_a, cols_b);
    matrix_mult(A, B, C, rows_a, cols_a, rows_b, cols_b); 
    print2Darray_p(C, rows_c, cols_c); printf("\n");

    free2Darray(A, rows_a, cols_a); free2Darray(B, rows_b, cols_b); free2Darray(C, rows_c, cols_c);

    rows = 3, cols = 5;
    A = get_2d_array(rows, cols); matrix_populate(A, rows, cols); print2Darray_p(A, rows, cols); printf("\n");
    B = get_2d_array(cols, rows);
    matrix_transpose(A, B, rows, cols);
    print2Darray_p(B, cols, rows); printf("\n");
    free2Darray(A, rows, cols); free2Darray(B, cols, rows); 

    list item1, item2, item3;
    item1.data = 'a'; item2.data = 'b'; item3.data = 'c';
    item1.link = &item2; item2.link = &item3; item3.link = NULL; 
    printf("%c\n", item1.data);
    printf("%c\n", item1.link->data);
    printf("%c\n", item1.link->link->data);


}
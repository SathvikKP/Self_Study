#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "utils.h"

struct sparse_matrix{
    int row;
    int col;
    int val;
};

typedef struct sparse_matrix sparse_matrix;

sparse_matrix* get_new_sparse_matrix(int size) {
    sparse_matrix* A = NULL;
    MALLOC(A, size*sizeof(sparse_matrix));
    dealloc_warn();
    return A;
}

void initialize_sparse_matrix(sparse_matrix A[], int rows[], int cols[], int vals[], int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        A[i].row = rows[i];
        A[i].col = cols[i];
        A[i].val = vals[i];
    }
}

void print_sparse_matrix(sparse_matrix A[], int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        printf("%4d %4d %4d\n", A[i].row, A[i].col, A[i].val);
    }
    printf("\n");
}

void sparse_matrix_transpose(sparse_matrix A[], sparse_matrix B[]) {
    
    int i = 0, j = 0, currentB = 0;

    B[0].row = A[0].col;
    B[0].col = A[0].row;
    B[0].val = A[0].val;

    if (A[0].val == 0) {
        return;
    }
    currentB = 1;
    for (i = 0; i < A[0].col; i++) {
        for (j = 1; j <= A[0].val; j++) {
            if (A[j].col == i) {
                B[currentB].row = A[j].col;
                B[currentB].col = A[j].row;
                B[currentB].val = A[j].val;
                currentB++;
            }
        }
    }
    
}

void sparse_matrix_fast_transpose(sparse_matrix A[], sparse_matrix B[]) {

    int i = 0, j = 0, num_cols_A = A[0].col, num_elems = A[0].val;
    
    int* row_terms_B = NULL;
    row_terms_B = get_zero_array(num_cols_A);
    int* starting_pos_B = NULL;
    starting_pos_B = get_zero_array(num_cols_A);

    if (num_elems == 0) {
        return;
    }

    for (i = 1; i <= num_elems; i++) {
        row_terms_B[A[i].col]++;
    }
    starting_pos_B[0] = 1;
    for (i = 1; i < num_cols_A; i++) {
        starting_pos_B[i] = starting_pos_B[i-1] + row_terms_B[i-1];
    }

    printf("\n"); printarray_p(row_terms_B, num_cols_A);
    printarray_p(starting_pos_B, num_cols_A); printf("\n");
    
    B[0].row = A[0].col;
    B[0].col = A[0].row;
    B[0].val = A[0].val;

    for (i = 1; i <= num_elems; i++) {
        j = starting_pos_B[A[i].col]++;
        B[j].col = A[i].row;
        B[j].row = A[i].col;
        B[j].val = A[i].val;
    }

    if (row_terms_B) {free(row_terms_B);}
    if (starting_pos_B) {free(starting_pos_B);}

}

void sparse_matrix_driver() {
    int size = 9;
    int rows[9] = {6, 0, 0, 0, 1, 1, 2, 4, 5};
    int cols[9] = {6, 0, 3, 5, 1, 2, 3, 0, 2};
    int vals[9] = {8, 15, 22, -15, 11, 3, -6, 91, 28};
    sparse_matrix* A = NULL;
    A = get_new_sparse_matrix(size);
    initialize_sparse_matrix(A, rows, cols, vals, size);
    print_sparse_matrix(A, A[0].val+1);

    sparse_matrix* B = NULL;
    B = get_new_sparse_matrix(size);
    //sparse_matrix_transpose(A, B);
    sparse_matrix_fast_transpose(A, B);
    print_sparse_matrix(B, B[0].val+1);

    if (A) {free(A);};
    if (B) {free(B);};
}
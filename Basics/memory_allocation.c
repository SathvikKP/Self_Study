#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void memory_allocation() {
    int i, *pi; //warning : initialise
    float f, *pf;

    pi = (int*) malloc(sizeof(int));
    pf = (float*) malloc(sizeof(float));

    *pi = 4;
    *pf = 3.1416;

    printf("%d\n", *pi );
    printf("%f\n", *pf );

    free(pi);
    free(pf);

    int *px;
    MALLOC(px,sizeof(int));
    *px = 100;
    printint(1,*px);
    free(px);

    //dynamic memory allocation via function

    int *A = NULL, A_len = 0 ;
    char file_name[] = "test_input_file.txt";

    
    read_int_from_file(file_name, sizeof(file_name), &A, &A_len);

    /*for (int i = 0 ; i < A_len; i++) {
        printf("%d ", *(A+i));
    }*/
    printarray_p(&A, A_len);
    free(A);

    int *B = NULL;
    int B_size = 25;
    int B_max_val = 500;
    generate_random_int_array(&B, B_size, B_max_val);
    printarray_p(&B, B_size);
    free(B);
}


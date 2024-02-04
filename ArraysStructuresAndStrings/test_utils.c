#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "utils.h"

void run_test_utils() {

    print("void print(char*); \nUncomment a test case in test_utils.c! \n ");

    /*
    print("void printint(int, ...);");
    printint(1, 4);
    printint(5, 7, 4, 4, 4, 5);
    */

    /*
    print("void printdouble(int num, ...);");
    printdouble(1, 3.6767);
    printdouble(3, 23.3, 53.2, -76.666);
    */

    /*
    print("void printarray(int[], int);");
    int array_1[] = {1,2,3,4,5}; int array_1_size = 5;
    printarray(array_1, array_1_size);
    */

    /*
    print("void printarray_p(int*, int)");
    int* array_2 = NULL; int array_2_size = 10; array_2 = (int*)malloc(array_2_size*sizeof(int));
    for (int i = 0; i < array_2_size; i++) {array_2[i] = i;} printarray_p(array_2, array_2_size); free(array_2);
    */

    /*
    print("void print2Darray(int m, int n, int[m][n]);");
    int m = 4, n = 5, count = 1; int array_2d_1[m][n]; memset(array_2d_1, 0, (sizeof(int)*n*n));
    for (int i = 0; i < m; i++) { for (int j = 0; j < n; j++) { array_2d_1[i][j] = count++; } }
    print2Darray(m, n, array_2d_1);
    */
    
    /*
    print("int* get_zero_array(int);");
    int num_zeroes = 5; int* zero_array = get_zero_array(num_zeroes); 
    printarray_p(zero_array, num_zeroes); free(zero_array);
    */

    /*
    print("int* get_array(int);");
    int num_elem = 5; int* array_uninit = get_array(num_elem); 
    printarray_p(array_uninit, num_elem); free(array_uninit);
    */
    
    /*
    print("int* generate_random_int_array(int, int);");
    int size = 10, max_val = 300; int* random_array_1 = generate_random_int_array(size, max_val);
    printarray_p(random_array_1, size); free(random_array_1);
    */

    /*
    print("int* read_int_from_file(char[], int*);");
    int array_size = 0; int* file_array = read_int_from_file("test_input_file.txt", &array_size);
    printarray_p(file_array, array_size);
    */

    
    /*
    print("int** get_2d_array(int, int); \nvoid print2Darray_p(int**, int, int);"
        "\nvoid free2Darray(int**, int, int); ");
    int m = 5, n = 4; int** array_2d_2 = get_2d_array(m, n); 
    print2Darray_p(array_2d_2, m, n); free2Darray(array_2d_2, m, n);
    */


}
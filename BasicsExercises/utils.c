#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "utils.h"

void printint(int num, ...) {
    
    int i = 0;
    va_list list;
    va_start(list, num);
    for (i = 0; i < num; i++){
        printf("%d\n",va_arg(list, int));
    }
    va_end(list);
}

void printdouble(int num, ...) {
    
    int i = 0;
    va_list list;
    va_start(list, num);
    for (i = 0; i < num; i++){
        printf("%f\n",va_arg(list, double));
    }
    va_end(list);
}

void printarray_p(int** array, int array_size) {
    int i = 0;
    for (i = 0; i < array_size; i++) {
        printf("%d ",*((*array)+i));
    }
    printf("\n");
}

void printarray(int array[], int array_size) {
    int i = 0;
    for (i = 0; i < array_size; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
}

void print2Darray(int m, int n, int array[m][n]) {
    int i = 0, j = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }
}

void dealloc_warn() {
    printf("\nTake care to deallocate memory in caller function!\n");
}

void read_int_from_file(char file_name[], size_t file_name_size, int** array, int* array_len) {

    int i = 0;
    int n = 0;
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("FILE NOT FOUND!\n"); exit(1);
    }
    //get number of integers from first line of file
    fscanf(file, "%d", &n); 
    //assign the array length to main function variable pointer
    *array_len = n; //printf("%d\n",*array_len);
    //allocate memory
    MALLOC(*array,n*sizeof(int)); //*array = (int*)malloc(n*sizeof(int));
    dealloc_warn();
    //read remaining integers
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", (*array)+i); // fscanf(file, "%d", &x);*((*array)+i) = x ;//or (*array)[i] = x;
    }
    
    fclose(file);
    
}

void generate_random_int_array(int** array, int array_size, int max_val) {
    
    srand(time(NULL));
    MALLOC(*array, array_size*sizeof(int));
    dealloc_warn();

    for (int i = 0; i < array_size ; i++) {
        *(*(array)+i) = rand()%max_val;
    }

}

/*
void get_2d_array(int** array, int rows, int cols) {
    int i = 0;
    MALLOC(array, rows*sizeof(int*));
    for (i = 0; i < rows; i++) {
        //CALLOC(array[i], 0, cols*sizeof(int));
        MALLOC(array[i], cols*sizeof(int));
    }
    dealloc_warn();
}
*/

int** get_2d_array(int rows, int cols) {
    int** array = NULL;
    int i = 0;
    MALLOC(array, rows*sizeof(int*));
    for (i = 0; i < rows; i++) {
        CALLOC(array[i], cols, sizeof(int));
    }
    return array;
}

void print2Darray_p(int** array, int rows, int cols) {
    int i = 0, j = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            //printf("%d ", *(((*array)+i)+j)); //or array[i][j]
            printf("%4d ", array[i][j]);
        }
        printf("\n");
    }
}
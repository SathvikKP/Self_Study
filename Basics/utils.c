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

void printarray_p(int** array, int array_size) {
    int i = 0;
    for (int i = 0; i < array_size; i++) {
        printf("%d ",*((*array)+i));
    }
    printf("\n");
}

void printarray(int array[], int array_size) {
    int i = 0;
    for (int i = 0; i < array_size; i++) {
        printf("%d ",array[i]);
    }
    printf("\n");
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
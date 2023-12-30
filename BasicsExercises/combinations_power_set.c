#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "utils.h"

//[1,2,3]
//[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]

void print_element_combinations(int arr[], int bool_arr[], int arr_size) {
    int i = 0;
    printf("\"");
    for (i = 0; i < arr_size; i++) {
        if (bool_arr[i] == 1) {
            printf("%d ",arr[i]);
        }
    }
    printf("\"\n");
}

void combination_boolean_permute(int arr[], int bool_arr[], int arr_size, int index) {
    if (index == arr_size) {
        print_element_combinations(arr, bool_arr, arr_size);
    }
    else {
        bool_arr[index] = 0;
        combination_boolean_permute(arr, bool_arr, arr_size, index+1);
        bool_arr[index] = 1;
        combination_boolean_permute(arr, bool_arr, arr_size, index+1);
    }
}

void power_set(int arr[], int arr_size) {
    int bool_arr[arr_size];
    memset(bool_arr, 0, arr_size*sizeof(int));
    combination_boolean_permute(arr, bool_arr, arr_size, 0);
}

void power_set_driver() {
    int arr[] = {1,2,3,4};
    int arr_size = 4;
    /*int reverse_arr[arr_size];
    int i = 0;
    memset(reverse_arr, 0, sizeof(int)*arr_size);
    for (i = 0; i < arr_size; i++){
        reverse_arr[i] = arr[arr_size - 1 - i];
    }*/
    power_set(arr,arr_size);
}
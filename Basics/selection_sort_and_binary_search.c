#include <stdio.h>
#include "utils.h"

void selection_sort_p(int** array, int array_size) {
    
    int i = 0;
    int j = 0;
    int temp = 0;
    int min_index = 0;

    //keeping 1st element, scan rest of array to find minimum element,
    // swap that with 1st element, proceed forward
   
    for (i = 0; i < array_size - 1; i++) {
        min_index = i;
        for (j = i+1; j < array_size ; j++) {
            if (*((*array)+j) < *((*array)+min_index)) {
                min_index = j;
            }
        }
        SWAP((*array)[i], (*array)[min_index], temp);
    }
}

void selection_sort(int arr[], int arr_size) {
    int i = 0;
    int j = 0;
    int min_index = 0;
    int temp = 0;

    for (i = 0; i < arr_size -1; i++) {
        min_index = i;
        for (j = i + 1; j < arr_size ; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        SWAP(arr[i], arr[min_index], temp);
    }
}

int binary_search_normal(int array[], int array_size, int target) {
    int left = 0;
    int right = array_size-1;
    int middle = 0;

    // "<=" and not "<" because search for 4 in [1, 2, 3, 4]

    while (left <= right) {                     
        middle = (left + right) / 2;
        switch (COMPARE(target , array[middle])) {
            case -1: right = middle - 1; break;
            case 0: return middle;
            case 1: left = middle + 1; break;
        }
    } 
    return -1;
}

int binary_search_recursive(int array[], int left, int right, int target) {
    int middle = (left + right) / 2;
    if (left <= right) {
        switch (COMPARE(target, array[middle])) {
            case -1 : return binary_search_recursive(array, left, middle - 1, target);
            case 0 : return middle;
            case 1 : return binary_search_recursive(array, middle + 1, right, target);
        }
    }
    return -1;
}

int binary_search(int array[], int array_size, int target) {
    int left = 0;
    int right = array_size - 1;
    return binary_search_recursive(array, left ,right ,target);
}

void selection_sort_driver() {

    int i = 0;

    //selection sort main array
    int *array = NULL;
    int array_size = 30;
    int array_max_val = 200;

    //search targets array for binary search 
    int* search_targets = NULL;
    int search_targets_size = 10;
    int search_targets_max_val = 150;

//selectionsort

    generate_random_int_array(&array, array_size, array_max_val);
    printarray(array, array_size);
    selection_sort(array, array_size);
    //selection_sort_p(&array, array_size);
    printarray(array, array_size);

//binarysearch

    generate_random_int_array(&search_targets, search_targets_size, search_targets_max_val);
    selection_sort(search_targets, search_targets_size);
    printarray(search_targets, search_targets_size);
    printf("\n");

    for (i = 0; i < search_targets_size; i++ ) {
        //printf("%d : %d \n",search_targets[i],binary_search_normal(array, array_size, search_targets[i]));
        printf("%d : %d \n",search_targets[i],binary_search(array, array_size, search_targets[i]));
    }

    if (array) { free(array); }
    if (search_targets) { free(search_targets); }

}


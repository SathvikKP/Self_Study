#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>

void boolean_permute(int arr[], int index, int n) {
    if (index == n) {
        printarray(arr,n);
    }
    else {
        arr[index] = 0;
        boolean_permute(arr, index+1, n);
        arr[index] = 1;
        boolean_permute(arr, index+1, n);
    }
}

void boolean_permute_driver() {
    int n = 5;
    int arr[n];
    memset(arr, 0, sizeof(int)*n);
    boolean_permute(arr, 0, n);
}
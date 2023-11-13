#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/*n >= 1 for fibonacci and n>=0 for factorial*/

int factorialI(int n) {
    int result = 1;
    int i = 0;
    for (i = 1 ; i <= n ; i++) {
        result *=i;
    }
    return result;
}

int factorialR(int n) {
    switch(n) {
        case 0: return 1;
        case 1: return 1;
        default: return n*factorialR(n-1);
    }
}

int* fibonacciI(int n) {
    int* array = NULL;
    MALLOC(array, n*sizeof(int));
    int i = 0;
    if (n == 1) {
        array[0] = 0; return array;
    }
    else if (n == 2) {
        array[0] = 0; array[1] = 1; return array; 
    }
    else {
        array[0] = 0; array[1] = 1;
        for (i = 2; i < n; i++) {
            array[i] = array[i-1] + array[i-2];
        }
        return array;
    }
}

int fibonacciR(int n) {
    switch (n) {
        case 0: return 0;
        case 1: return 1;
        default: return fibonacciR(n-1) + fibonacciR(n-2);
    }
}

int* fibonacciRecursive(int n) {
    //very bad time complexity !!!
    int* array = NULL;
    MALLOC(array, n*sizeof(int));
    for (int i = 0 ; i < n ; i++) {
        array[i] = fibonacciR(i);
    }
    return array;
}

int factorial_fibonaci_driver() {

    int x = 5;

    printint(1, factorialI(x));
    printint(1, factorialR(x));

    int* arr = NULL;
    int arr_size = 15;
    arr = fibonacciI(arr_size);
    printarray(arr,arr_size);
    free(arr);

    arr = fibonacciRecursive(arr_size);
    printarray(arr,arr_size);
    free(arr);

}
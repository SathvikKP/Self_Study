#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "utils.h"

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

int gcd_I(int a, int b) {
    //not sure about logic
    
    while (a > 1 && b > 1) {
        //printint(2, a, b);
        if (a > b) {
            if (a % b == 0) {
                return b;
            }
            else {
                a = a % b;
            }
        }
        else if (b > a) {
            if (b % a == 0) {
                return a;
            }
            else {
                b = b % a;
            }
        }
    }
}

int gcd_euclids(int a, int b) {
    if (a == 0) {
        return b;
    }
    else if (b == 0) {
        return a;
    }
    while (a != b) {
        if (a > b) {
            a = a - b;
        }
        else {
            b = b - a;
        }
        //printint(2, a, b);
    }
    return a;
}

double square_root_manual(int n) {
    
    int l = 0;
    int r = n;
    int mid = 0;
    double ans = 0;
    double incr = 0.1;
    int i = 0;
    int j = 0;

    while (l <= r) {
        
        mid = (l + r) / 2;

        if ((mid * mid) == n) {
            return mid;
        }
        
        if ((mid * mid) < n) {
            ans = mid;
            l = mid + 1;
        }
        else {
            r = l - 1;
        }
    }

    for (i = 0; i < 5; i++) {
        while (ans * ans <= n) {
            ans = ans + incr;
        }
        ans = ans - incr;
        incr = incr / 10;
    }

    return ans;

}

int floor_double_manual(float n) {
    return (int) n;
}

int ceil_double_manual(float n) {
    return ((int) n) + 1;
}

int* get_all_divisors(int n, int* num_div) {

    int* list = NULL;
    //MALLOC(list, 1*sizeof(int));
    int i = 0;
    int j = 0;
    double root = square_root_manual(n);
    printf("%2f",root);
    int min = 1;
    //int max = ceil_double_manual(root);
    //printf("%d",max);
    int size = 0;

    for (i = min; i < root; i++) {
        //printf("%d ",i);
        if (n % i == 0) {
            size = size+2;
            REALLOC(list, size*sizeof(int));
            list[j] = i;
            list[j+1] = n / i;
            j = j + 2;
        }
    }

    if (n % i == 0) {
        if (i * i == n) {
            size = size + 1;
            REALLOC(list, size*sizeof(int));
            list[j] = i;
            j = j + 1;
        }/*
        else {
            size = size+2;
            REALLOC(list, size*sizeof(int));
            list[j] = i;
            list[j+1] = n / i;
            j = j + 2;
        }*/
    }
    *num_div = size;
    dealloc_warn();
    return list;
}

int compare_function(const void *a,const void *b) {
    int *x = (int *) a;
    int *y = (int *) b;
    return *x - *y;
}

void gcd_and_divisors_driver() {

    int a = 735, b = 690;
    printint(1, gcd(a, b));
    printint(1, gcd_I(a, b));
    printint(1, gcd_euclids(a, b));
    
    int x = 5;
    printdouble(1, square_root_manual(x));
    printdouble(1, sqrt(x));

    int* arr = NULL;
    int n = 10250;
    int num_div = 0;
    arr = get_all_divisors(n, &num_div);
    printarray(arr, num_div);
    qsort(arr, num_div, sizeof(int), compare_function);
    printarray(arr, num_div);
    free(arr);

}
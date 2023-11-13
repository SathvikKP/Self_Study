#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

extern int factorialI(int n);
/*
nCr = n! / ((n-r)! * r!)
x! = x*(x-1)*(x-2)...1;
nCr = (n-1)Cr + (n-1)C(r-1)
*/

int binomial_coef_I(int n, int r) {
    int numerator = factorialI(n);
    int denominator = factorialI(n-r) * factorialI(r);
    return (numerator/denominator);
}

int binomial_coef_R(int n, int r) {
    if (r == 0) {
        return 1;
    }
    else if (n == r) {
        return 1;
    }
    else{
        return binomial_coef_R(n-1, r) + binomial_coef_R(n-1, r-1);
    }
}
/*
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
*/
/*
00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33
*/

int binomial_coef_M(int n, int r) {
    n++; r++;
    int i = 0,j = 0;
    int table[n][n];
    memset(table, 0, (sizeof(int)*n*n)); //or table[n][n] = {0};
    for (i = 0; i < n; i++) {
        table[i][j] = 1;
    }
    for (i = 1; i < n; i++) {
        for (j = 1; j <= i; j++) {
            table[i][j] = table[i-1][j] + table[i-1][j-1];
            if ((n - 1 == i) && (r - 1 == j)) {
                return table[i][j];
            }
        }
    }
    return table[0][0];
}

void binomial_coef_driver() {
    int n=4,r=2;
    clock_t start, end;
    double cpu_time_used;
    /*
    printint(1,binomial_coef_I(n,r));
    printint(1,binomial_coef_R(n,r));
    printint(1,binomial_coef_M(n,r));
    
    n=5;r=2;
    printint(1,binomial_coef_I(n,r));
    printint(1,binomial_coef_R(n,r));
    printint(1,binomial_coef_M(n,r));

    n=10;r=5;
    printint(1,binomial_coef_I(n,r));
    printint(1,binomial_coef_R(n,r));
    printint(1,binomial_coef_M(n,r));
    */

    n=30;r=10;

    start = clock();
    printint(1,binomial_coef_I(n,r));
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used for iterative: %f\n",cpu_time_used);

    start = clock();
    printint(1,binomial_coef_R(n,r));
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used for recursive: %f\n",cpu_time_used);

    start = clock();
    printint(1,binomial_coef_M(n,r));
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time used for memoization: %f\n",cpu_time_used);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

typedef long long ll;

int ackerman(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return ackerman(m - 1, 1);
    }
    else {
        return ackerman(m - 1, ackerman(m, n - 1));
    }
}

int ackerman_M(int m, int n) {

    m++; n++;
    //int max = (m > n ? m : n);
    int max = 10;
    int i = 0,j = 0;
    int table[max][max];
    memset(table, 0, max*max*sizeof(int));

    //for (j = 0; j < n; j++) {
    for (j = 0; j < max; j++) {
        table[i][j] = j + 1;
        if ((m - 1 == i) && (n - 1 == j)) {
            //return table[i][j];
        }
    }
    j = 0;

    for (i = 1; i < max; i++) {
        for (j = 0; j < max; j++) {
            if (j == 0) {
                table[i][j] = table[i-1][1];
            }
            else {
                table[i][j] = table[i-1][table[i][j-1]];
            }
        }
    }
    /*
    for (i = 1; i < m; i++) {
        table[i][j] = table[i-1][1]; 
        if ((m - 1 == i) && (n - 1 == j)) {
            //return table[i][j];
        }
    }
    i = 0; j = 0;
    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            table[i][j] = table[i-1][table[i][j-1]];
            if ((m - 1 == i) && (n - 1 == j)) {
                //return table[i][j];
            }
        }
    }*/
    print2Darray(max, max, table);
    return -1;

}

void ackerman_driver() {

    int m = 2, n = 2;
    printint(1, ackerman(m, n));
    //printint(1, ackerman_M(3, 3));

}
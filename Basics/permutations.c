#include <stdio.h>
#include <string.h>
#include "utils.h"

void permute(char* str, int i, int n){
    int j, temp;
    if (i == n) {
        puts(str);
    }
    else {
        for (j = i; j <= n; j++) {
            SWAP(str[i], str[j], temp );
            permute(str, i+1, n);
            SWAP(str[i], str[j], temp) ;

        }
    }
}

void permutation_driver() {
    char str[] = "abcd";
    permute(str, 0, strlen(str)-1);
}

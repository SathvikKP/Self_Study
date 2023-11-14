#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"




void TOH(int n, char source, char aux, char dest) {
    if (n == 1) {
        printf("Move disc %d from %c to %c\n", n, source, dest);
    }
    else {
        TOH(n-1, source, dest, aux);
        printf("Move disc %d from %c to %c\n", n, source, dest);
        TOH(n-1, aux, source, dest);
    }
}

int TOH_driver() {
    int n = 4;
    char source = 'A', aux = 'B', dest = 'C'; 
    TOH(n, source, aux, dest);
}
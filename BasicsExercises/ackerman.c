#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

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

void ackerman_driver() {

    int m = 2, n = 2;
    printint(1, ackerman(m, n));
}
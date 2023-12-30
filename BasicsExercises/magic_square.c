#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "utils.h"

void get_magic_square(int** array, int n) {
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    int count = 0;
    int limit = 0;
    /*First element 1 in top row middle column, then, go left and top, fill, if already filled, go down and continue*/
    i = 0; j = n/2; limit = n*n;
    array[i][j] = 1;

    for (count = 2; count <= limit; count++) {
        x = (i - 1 + n) % n; 
        y = (j - 1 + n) % n;
        //printf("x = %d, y = %d", x, y);
        if (array[x][y] == 0) {
            i = x; 
            j = y;
        }
        else {
            i = (i+1) % n;
        }
        array[i][j] = count;
    }
}


void magic_square_driver() {
    int** MS = NULL;
    int n = 7;
    MS = get_2d_array(n, n); //print2Darray_p(MS, n, n);

    get_magic_square(MS, n);
    print2Darray_p(MS, n, n);
    if (MS) { free(MS);}

}
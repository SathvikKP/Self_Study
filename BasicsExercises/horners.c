#include <stdio.h>
#include <stdlib.h>

void horners(int poly[], int n, int x) {

    int result = poly[0];
    int i = 0;
    for (i = 1; i <= n; i++) {
        result = poly[i] + x*result ;
    }
    printf("%d\n",result);

}

//2, -6, 2, -1 poly 0 3 2

//((2x – 6)x + 2)x – 1

int horners_recursive(int poly[], int i, int x) {

    if (i == 0) {
        return poly[i];
    }
    else {
        return poly[i] + x*horners_recursive(poly, i-1, x);
    }
}

void horner_driver() {

    int poly1[] = {2, -6, 2, -1}; //3
    
    horners(poly1, 3, 3);
    printf("%d\n",horners_recursive(poly1, 3, 3));


    int poly2[] = {2, 0, 3, 1}; //23

    horners(poly2, 3, 2);
    printf("%d\n",horners_recursive(poly2, 3, 2));

    int poly3[] = {3, 4, 6, 4, 2, 6}; //?

    horners(poly3, 5, 2); 
    printf("%d\n",horners_recursive(poly3, 5, 2)); 
}
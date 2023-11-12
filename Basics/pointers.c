#include <stdio.h>
#include "utils.h"

void checknull (int* p) { 
    if (p == NULL) {
        printf("NULL\n");
    }
    else {
        printf("NOT NULL : %d\n",*p);
    }
}

void pointers(){
    int i, *pi, *nullpi = NULL;
    pi = &i;
    i = 10;
    printf("%d\n", i);
    printf("%d\n", *pi);
    *pi = 20;
    printint(2, i, *pi);
    *pi = 30;
    checknull(pi);
    //*pi = NULL; //dangerous? assignment to ‘int’ from ‘void *’ makes integer from pointer without a cast
    
    checknull(nullpi);
}



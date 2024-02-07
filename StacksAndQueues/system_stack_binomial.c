#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "utils.h"


#define MAX_STACK_SIZE 100

/*basic element structure*/
struct element{
    int n;
    int r;
    /*other fields*/
};
typedef struct element element;

/*Stack definitions*/
int ss_top = -1;
element systemStack[MAX_STACK_SIZE];

void printSystemStack() {
    int i = 0;
    printf("\nStack (from top) :\n");
    for (i = ss_top; i >= 0 ; i--) {
        printf("binomial_coef_R(%d, %d)\n", systemStack[i].n, systemStack[i].r);
    }
    printf("\n");
}

void systemStackFull() {
    fprintf(stderr, "\nStack is full, cannot add element\n");
    printSystemStack();
    exit(EXIT_FAILURE);
}

element systemStackEmpty() {
    printf("\nStack is empty, cannot remove element");
    element item;
    item.n = -1;
    item.r = -1;
    return item;
}

void systemStackPush(element item) {
    if (ss_top >= MAX_STACK_SIZE - 1)
        systemStackFull();
    systemStack[++ss_top] = item;
}

element systemStackPop() {
    if (ss_top == -1)
        return systemStackEmpty();
    return systemStack[ss_top--];
}



int binomial_coef_R(int n, int r) {
    sleep(2);
    int return_val = -1;
    //printSystemStack();
    element item; item.n = n; item.r = r; systemStackPush(item);
    printf("Pushed item : binomial_coef_R(%d, %d)\n", item.n, item.r);
    printSystemStack();
    if (r == 0) {
        printf("r == 0, preparing to pop\n");
        item = systemStackPop(); 
        printf("Popped item : binomial_coef_R(%d, %d)\n", item.n, item.r);
        printSystemStack();
        return 1;
    }
    else if (n == r) {
        printf("n == r, preparing to pop\n");
        item = systemStackPop(); 
        printf("Popped item : binomial_coef_R(%d, %d)\n", item.n, item.r);
        printSystemStack();
        return 1;
    }
    else{
        printf("Preparing recursive call for binomial_coef_R(%d, %d) + binomial_coef_R(%d, %d)\n", n-1, r, n-1, r-1);
        printf("Calling binomial_coef_R(%d, %d)\n", n-1, r);
        int first_val = binomial_coef_R(n-1, r);
        printf("Returned from binomial_coef_R(%d, %d)\n", n-1, r);
        printf("Calling binomial_coef_R(%d, %d)\n", n-1, r-1);
        int second_val =  binomial_coef_R(n-1, r-1);
        printf("Returned from binomial_coef_R(%d, %d)\n", n-1, r-1);
        return_val = first_val + second_val;
        item = systemStackPop(); 
        printf("Popped item : binomial_coef_R(%d, %d)\n", item.n, item.r);
        printSystemStack();
        return return_val;
    }
}

void system_stack_binomial_driver() {
    int n = 6, r = 3;
    printSystemStack();
    printint(1,binomial_coef_R(n,r));
    printSystemStack();
}
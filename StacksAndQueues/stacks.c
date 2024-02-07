#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "utils.h"


#define MAX_STACK_SIZE 10

/*basic element structure*/
struct element{
    int key;
    /*other fields*/
};
typedef struct element element;

/*Stack definitions*/
int top = -1;
element stack[MAX_STACK_SIZE];

void printStack() {
    int i = 0;
    printf("\nPrinting stack from the top\n");
    for (i = top; i >= 0 ; i--) {
        printf("%d ", stack[i].key);
    }
    printf("\n");
}

void stackFull() {
    fprintf(stderr, "\nStack is full, cannot add element\n");
    printStack();
    exit(EXIT_FAILURE);
}

element stackEmpty() {
    printf("\nStack is empty, cannot remove element");
    element item;
    item.key = -1;
    return item;
}

void push(element item) {
    if (top >= MAX_STACK_SIZE - 1)
        stackFull();
    stack[++top] = item;
}

element pop() {
    if (top == -1)
        return stackEmpty();
    return stack[top--];
}



void simple_stack_driver() {
    printStack();
    int i = 0, j = 0;
    int elems[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int operations[25] = {0,1,1,1,1,0,0,1,0,1,0,1,1,1,0,0,0,1,0,1,0,1,1,0,1};
    for (i = 0; i < 25; i++) {
        sleep(1);
        if (operations[i] == 1) {
            element item; item.key = elems[j]; j++;
            push(item);
            printf("\nPushed element : %d", item.key);
        }
        else if (operations[i] == 0) {
            element item = pop();
            printf("\nPopped element : %d", item.key);
        }
    }
    printStack();
    for (j = 16; j < 30; j++) {
        element item; item.key = j; 
        printf("\nAttempting to push %d",item.key);
        push(item); 
        printf("\nPushed element : %d", item.key);
        //printf(" | top : %d\n",top);
        sleep(1);
    }
}
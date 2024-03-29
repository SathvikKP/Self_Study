#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../utils/utils.h"
#include "linked_list.h"

stackPointerLL top[MAX_STACKS_LL];
/*
    initial condition for stacks : 
    top[i] = NULL, 0 <= i < MAX_STACKS_LL
    top[i] = NULL if ith stack is empty
*/

void print_linked_stack(int stackNo) {
    if (stackNo >= MAX_STACKS_LL) return;
    stackPointerLL ptr = top[stackNo];
    printf("Stack %d : ",stackNo);
    while (ptr != NULL) {
        printf("%d -> ",ptr->data.key);
        ptr = ptr->link;
    }
    nl();
}

void push_ll_s(element item, int stackNo) {
    stackPointerLL pushItem = NULL;
    MALLOC(pushItem, sizeof(*pushItem));
    pushItem->data = item;
    pushItem->link = top[stackNo];
    top[stackNo] = pushItem;
}

void push_linked_stack(int value, int stackNo) {
    element item; //not initialized!!!
    item.key = value;
    if (stackNo >= MAX_STACKS_LL) return;
    push_ll_s(item, stackNo);
    printf("Element with value %d pushed to stack %d\n", value, stackNo);
    print_linked_stack(stackNo);
}

element pop_ll_s(int stackNo) {
    element item; //not initialized!!!
    stackPointerLL popItem = top[stackNo];
    if (top[stackNo] == NULL) {
        item.key = -42069;
        printf("Stack %d is empty\n",stackNo);
        return item;
    }
    top[stackNo] = top[stackNo]->link;
    item = popItem->data;
    free(popItem); popItem = NULL;
    return item;
}

//can be modified to return int or item
void pop_linked_stack(int stackNo) {
    element item; //not initialized!!!
    if (stackNo >= MAX_STACKS_LL) return;
    item = pop_ll_s(stackNo);
    if (item.key != -42069) {
        printf("Element with value %d popped from stack %d\n", item.key, stackNo);
    }
    print_linked_stack(stackNo);
}

void free_linked_stack(int stackNo) {
    element item;
    do {
        item = pop_ll_s(stackNo);
    } while (item.key != -42069);
}

void cleanup_linked_stacks() {
    int i;
    for (i = 0; i < MAX_STACKS_LL; i++) {
        free_linked_stack(i);
    }
}

void linked_stacks_driver() {

    //create 2 stacks, push and pop
    int i, j;

    int operations1[7] = {1, 1, 0, 1, 0, 1, 1};
    int data1[5] = {1, 2, 3, 4, 5};
    int operations2[8] = {0, 1, 1, 1, 1, 0, 0, 1};
    int data2[5] = {6, 7, 8, 9, 10};

    print_linked_stack(1);
    print_linked_stack(2); nl(); nl();

    for (i = 0, j = 0; i < 7; i++) {
        if (operations1[i] == 1) {
            push_linked_stack(data1[j], 1);
            j++;
        } else {
            pop_linked_stack(1);
        }
    }
    nl(); nl();
    for (i = 0, j = 0; i < 8; i++) {
        if (operations2[i] == 1) {
            push_linked_stack(data2[j], 2);
            j++;
        } else {
            pop_linked_stack(2);
        }
    }
    nl(); print_linked_stack(1);
    print_linked_stack(2); nl();

    pop_linked_stack(3); nl(); nl();

    cleanup_linked_stacks();

}
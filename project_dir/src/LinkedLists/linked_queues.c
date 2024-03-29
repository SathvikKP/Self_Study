#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../utils/utils.h"
#include "linked_list.h"

queuePointer front[MAX_QUEUES_LL];
queuePointer rear[MAX_QUEUES_LL];
/*
    initial condition for queues : 
    front[i] = NULL, 0 <= i < MAX_QUEUES_LL
    rear[i] = NULL, 0 <= i < MAX_QUEUES_LL
    front[i] = NULL if ith queue is empty
    elements added to rear[i]
*/


void print_linked_queue(int queueNo) {
    if (queueNo >= MAX_QUEUES_LL) return;
    queuePointer ptr = front[queueNo];
    printf("Queue %d : ",queueNo);
    while (ptr != NULL) {
        printf("%d -> ",ptr->data.key);
        ptr = ptr->link;
    }
    nl();
}

void addq_ll_q(element item, int queueNo) {
    queuePointer addItem = NULL;
    MALLOC(addItem, sizeof(*addItem));
    addItem->data = item;
    addItem->link = NULL;
    if (front[queueNo] == NULL) {
        front[queueNo] = addItem;
    }
    else {
        rear[queueNo]->link = addItem;
    }
    rear[queueNo] = addItem;
}

void addq_linked_queue(int value, int queueNo) {
    element item; //not initialized!!!
    item.key = value;
    if (queueNo >= MAX_QUEUES_LL) return;
    addq_ll_q(item, queueNo);
    printf("Element with value %d added to queue %d\n", value, queueNo);
    print_linked_queue(queueNo);
}

element deleteq_ll_q(int queueNo) {
    element item; //not initialized!!
    queuePointer deleteItem = front[queueNo];
    if (deleteItem == NULL) {
        item.key = -42069;
        printf("Queue %d is empty\n", queueNo);
        return item;
    }
    front[queueNo] = front[queueNo]->link;
    item = deleteItem->data;
    free(deleteItem); deleteItem = NULL;
    return item;
}

void deleteq_linked_queue(int queueNo) {
    element item; //not initialized!!!
    if (queueNo >= MAX_QUEUES_LL) return;
    item = deleteq_ll_q(queueNo);
    if (item.key != -42069) {
        printf("Element with value %d deleted from queue %d\n", item.key, queueNo);
    }
    print_linked_queue(queueNo);
}

void free_linked_queue(int queueNo) {
    element item;
    do {
        item = deleteq_ll_q(queueNo);
        //printf("element deleted\n");
    } while (item.key != -42069);
}

void cleanup_linked_queues() {
    int i;
    for (i = 0; i < MAX_QUEUES_LL; i++) {
        free_linked_queue(i);
    }
}

void linked_queues_driver() {

    //create 2 queues, add and deletes
    int i, j;

    int operations1[7] = {1, 1, 0, 1, 0, 1, 1};
    int data1[5] = {1, 2, 3, 4, 5};
    int operations2[8] = {0, 1, 1, 1, 1, 0, 0, 1};
    int data2[5] = {6, 7, 8, 9, 10};

    print_linked_queue(1);
    print_linked_queue(2); nl(); nl();

    for (i = 0, j = 0; i < 7; i++) {
        if (operations1[i] == 1) {
            addq_linked_queue(data1[j], 1);
            j++;
        } else {
            deleteq_linked_queue(1);
        }
    }
    nl(); nl();
    for (i = 0, j = 0; i < 8; i++) {
        if (operations2[i] == 1) {
            addq_linked_queue(data2[j], 2);
            j++;
        } else {
            deleteq_linked_queue(2);
        }
    }
    nl(); print_linked_queue(1);
    print_linked_queue(2); nl();

    deleteq_linked_queue(3); nl(); nl();

    cleanup_linked_queues();


}
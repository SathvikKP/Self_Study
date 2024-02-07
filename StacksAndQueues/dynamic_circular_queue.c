#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "utils.h"

/*element details*/
struct qElement {
    int key;
    /*other fields*/
};
typedef struct qElement qElement;

/*Queue Details*/
qElement *queue = NULL;
int capacity = 1;
int front = 0;
int rear = 0;

/*Queue functions*/

void displayQueueClassic() {
    int i = 0;
    printf("front = %d, rear = %d, capacity = %d\n", front, rear, capacity);
    for (i = 0; i < capacity; i++) {
        printf("%2d ",i);
    }
    printf("\n");
    for (i = 0; i < capacity; i++) {
        printf("%2d ",queue[i].key);
    }
    printf("\n");
}

void displayQueue() {
    int i = 0;
    for (i = (front+1)%capacity; i != (rear+1)%capacity; i = (i+1)%capacity) {
        printf("%2d ",queue[i].key);
    }
    printf("\n");
}

void queueCopy(qElement* startingPos, qElement* endingPos, qElement* newQueue) {
    int i = 0;
    while (startingPos < endingPos) {
        *(newQueue + i) = *startingPos;
        startingPos++;
        i++;
    }
}

void queueFull() {
    
    int start = 0;
    qElement *newQueue = NULL;
    MALLOC(newQueue, sizeof(qElement)*2*capacity);

    /* There are 3 cases 
    1st case --> queue begins at queue[0]
                R F
    0 1 2 3 4 5 6 7 
    A B C D E F G 
    In this case, we need to copy from queue[0] till queue[R]

    2nd case --> queue begins at queue[1]
    F             R
    0 1 2 3 4 5 6 7 
      A B C D E F G
    In this case, we need to copy from queue[1] till queue[R]

    3rd case --> queue begins at any other position
          R F
    0 1 2 3 4 5 6 7 
    D E F G   A B C 
    In this case, we need to copy from queue[F+1] till queue[capacity-1], then copy from queue[0] till queue[R]
    
    
    We can simplify implementation by calculating starting position
    start = (front+1)%capacity
    So, for the first 2 cases, starting pos < 2 --> we copy from queue[start] --> queue[R] (or queue[start+capacity-1]);
    copy(0,7) and copy(1,8);
    For the third case, perform 2 copies. copy(5,8) and copy(0,4);
    
    */
    start = (front+1)%capacity;
    
    if (start < 2) {
        queueCopy(queue+start, queue+start+capacity-1, newQueue);
    }
    else {
        queueCopy(queue+start, queue+capacity, newQueue);
        queueCopy(queue, queue+rear+1, newQueue+capacity-start); 
    }
    front = 2*capacity - 1;
    rear = capacity - 2; /*Be careful about this operation!!*/
    capacity *= 2;
    if (queue) { free(queue);}
    queue = newQueue;
}

qElement queueEmpty() {
    printf("Queue is empty!\n");
    qElement item;
    item.key = -1;
    return item;
}

void addq(qElement item) {
    rear = (rear + 1) % capacity;
    if (front == rear) {
        queueFull();
        rear = (rear + 1) % capacity; /*Why?*/
    }
    queue[rear] = item;
}

qElement deleteq() {
    if (front == rear) {
        return queueEmpty();
    }
    front = (front+1) % capacity;
    return queue[front];
}


void dynamic_queue_driver() {

    MALLOC(queue, sizeof(qElement)*capacity);

    int choice = 0, i = 0;
    int itemval = 0;
    qElement item;
    do {
        //printf("front = %d, rear = %d, capacity = %d\n", front, rear, capacity);
        //displayQueueClassic();
        printf("1: Push, 2: Pop, 3:DisplayClassic, 4: Display\nEnter choice : ");
        scanf("%d",&choice); //printf("\n");
        switch(choice) {
            case 1: 
                printf("Enter element to add : "); scanf("%d",&itemval); //printf("\n");
                item.key = itemval; addq(item); printf("Item addded!\n");
                break;
            case 2:
                item = deleteq();
                if (item.key != -1) {
                    printf("Item deleted : %d\n",item.key);
                }
                break;
            case 3:
                displayQueueClassic();
                break;
            case 4:
                displayQueue();
                break;
            default:
                choice = -1;
                break;
        }

    } while(choice != -1);

    if (queue) {free(queue);}

}
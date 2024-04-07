#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../utils/utils.h"
#include "linked_list.h"

#define FALSE 0
#define TRUE 1
#define MAX_EQ_CLASS_VAL 12 /*actual max val + 1 for convinience*/

struct pair{
    int x;
    int y;
};

int list_free_count = 0;
int list_malloc_count = 0;

/*
int num_pairs = 9, max_val = 11, min_val = 0;
struct pair pair_array[9] = { {0, 4}, {3, 1}, {6, 10}, {8, 9}, {7, 4}, {6, 8}, {3, 5}, {2, 11}, {11, 0} };

phase 1 :

(links are reversed in the implementation!!)

0  -> [11] -> [4]
1  -> [3]
2  -> [11]
3  -> [5]  -> [1]
4  -> [7]  -> [0]
5  -> [3]
6  -> [8]  -> [10]
7  -> [4]
8  -> [6]  -> [9]
9  -> [8]
10 -> [6]
11 -> [0]  -> [2]
.
.

phase 2:

output 0, 11, 4 

Stack contents NULL <- 11 <- 4
      NULL
        ^
        |
0  -> [11] <- [4]
1  -> [3]
2  -> [11]
3  -> [5]  -> [1]
4  -> [7]  -> [0]
5  -> [3]
6  -> [8]  -> [10]
7  -> [4]
8  -> [6]  -> [9]
9  -> [8]
10 -> [6]
11 -> [0]  -> [2]


*/


void ll_eq_class_print_sequence(intListPointer seq[]) {
    //intListPointer current[] = seq[];
    intListPointer temp = NULL;
    int i = 0;
    for (i = 0; i < MAX_EQ_CLASS_VAL; i++) {
        printf("%d | ", i);
        temp = seq[i];
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
}

void ll_print_eq_class(intListPointer seq[], int out[]) {

    int i = 0, j = 0;
    intListPointer x = NULL, y = NULL, top = NULL;

    for (i = 0; i < MAX_EQ_CLASS_VAL; i++) {

        if (out[i] == FALSE) {

            printf("\nClass : %d ",i); out[i] = TRUE;
            x = seq[i]; top = NULL;

            for ( ; ; ) {
                /*Infinite loop*/
                while (x) {
                    j = x->data;
                    if (out[j] == FALSE) {
                        printf(" %d ", j); out[j] = TRUE;
                        /*Add x to the stack pointed by top, move x*/
                        y = x->link; x->link = top; top = x; x = y; 
                    } else {
                        /*Need to free here*/
                        y = x;
                        x = x->link; //Move x to next
                        if (y) free(y);
                        list_free_count++;
                    }
                } //end while
                /*unstack from stack and assign to x, free unstacked nodes*/
                if (!top) break; //if end is reached, go to next iteration of i
                x = seq[top->data];
                y = top;
                top = top->link; //unstack
                if (y) free(y);
                list_free_count++;
            }

        }

    }

}

void linked_list_equivalence_class_driver() {

    printf("\nNote : This program does not attempt to clean memory properly and elegantly!!\n");

    int num_pairs = 9;
    int i = 0, x = 0, y = 0;
    struct pair pair_array[9] = { {0, 4}, {3, 1}, {6, 10}, {8, 9}, {7, 4}, {6, 8}, {3, 5}, {2, 11}, {11, 0} };

    intListPointer seq[MAX_EQ_CLASS_VAL];
    intListPointer node = NULL;
    int out[MAX_EQ_CLASS_VAL];

    /*initialize*/
    for (int i = 0; i < MAX_EQ_CLASS_VAL; i++) {
        seq[i] = NULL; out[i] = FALSE;
    }

    ll_eq_class_print_sequence(seq); nl();

    /*Phase 1 : Construct the initial array of lists*/

    for (i = 0; i < num_pairs; i++) {
        x = pair_array[i].x; y = pair_array[i].y;
        node = create_intListNode(y); list_malloc_count++;
        node->link = seq[x]; seq[x] = node; node = NULL;
        node = create_intListNode(x); list_malloc_count++;
        node->link = seq[y]; seq[y] = node; node = NULL;
    }

    ll_eq_class_print_sequence(seq);

    /*Phase 2 : print out the classes!*/
    ll_print_eq_class(seq, out);

    if (list_free_count == list_malloc_count) {
        //ll_eq_class_print_sequence(seq);
        printf("\n\nMemory freed properly!\n");
    }
    else {
        printf("\n list_free_count = %d, list_malloc_count = %d", list_free_count, list_malloc_count);
        printf("\nIncorrect memory management : memory leak!\n");
        //ll_eq_class_print_sequence(seq); nl();
    }
}
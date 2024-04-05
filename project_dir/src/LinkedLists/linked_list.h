#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../utils/utils.h"

#define MAX_STACKS_LL 10
#define MAX_QUEUES_LL 10

typedef struct intListNode intListNode; //forward declaration
typedef struct intListNode *intListPointer;
struct intListNode{
    int data;
    intListPointer link;
};

typedef struct element element;
struct element{
    int key;
};

typedef struct stackLL stackLL;
typedef struct stackLL *stackPointerLL;
struct stackLL{
    element data;
    stackPointerLL link;
};

typedef struct queueLL queueLL;
typedef struct queueLL *queuePointer;
struct queueLL{
    element data;
    queuePointer link;
};


typedef struct polyNode polyNode;
typedef struct polyNode *polyPointer;
struct polyNode {
    int coef;
    int expon;
    polyPointer link;
};

//driver functions
void linked_list_driver();
void simple_int_linked_list_driver();
void int_linked_list_advanced_driver();
void linked_stacks_driver();
void linked_queues_driver();
void linked_list_polynomial_driver();

//simple_int_linked_list.c functions

intListPointer create_intListNode(int x);
void print_intList(intListPointer first);
void free_intList(intListPointer* first_p);
intListPointer search_intList(intListPointer first, int x);
void insert_end_intList(intListPointer* first_p, int x);
void insert_after_node_intList(intListPointer *first, intListPointer node, int val);
void insert_at_beginning_intList(intListPointer *first_p, int val);
void delete_node_by_value_intList_2n(intListPointer *first_p, int val);
void delete_node_by_value_intList(intListPointer *first_p, int val);
void search_intList_driver(intListPointer list, int val);
void insert_after_node_intList_driver(intListPointer *first_p, int pos, int val);

//int_linked_list_advanced.c functions
void insert_non_decreasing_intList(intListPointer *first_p, int val);
intListPointer merge_intList_non_decreasing(intListPointer *list1_p, intListPointer *list2_p);
void invert_intList(intListPointer* first_p);

//linked_stacks.c functions
void print_linked_stack(int stackNo);
void push_ll_s(element item, int stackNo);
void push_linked_stack(int value, int stackNo);
element pop_ll_s(int stackNo);
void pop_linked_stack(int stackNo);
void free_linked_stack(int stackNo);
void cleanup_linked_stacks();


//linked_queues.c functions
void print_linked_queue(int queueNo);
void addq_ll_q(element item, int queueNo);
void addq_linked_queue(int value, int queueNo);
element deleteq_ll_q(int queueNo);
void deleteq_linked_queue(int queueNo);
void free_linked_queue(int queueNo);
void cleanup_linked_queues();


//linked_list_polynomial functions
void ll_print_polynomial(polyPointer polynomial);
polyPointer ll_create_polynomial_node(int coef, int expon);
polyPointer ll_create_polynomial(int coef_array[], int expon_array[], int array_size);
void ll_free_polynomial(polyPointer *polynomial);
polyPointer ll_add_polynomial(polyPointer polyA, polyPointer polyB);

#endif
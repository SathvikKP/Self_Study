#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../utils/utils.h"


typedef struct intListNode intListNode; //forward declaration
typedef struct intListNode *intListPointer;
struct intListNode{
    int data;
    intListPointer link;
};

//driver functions
void linked_list_driver();
void simple_int_linked_list_driver();
void int_linked_list_advanced_driver();

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


#endif
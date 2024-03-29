#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../utils/utils.h"
#include "linked_list.h"

intListPointer create_intListNode(int x) {
    intListPointer newnode = NULL;
    MALLOC(newnode, sizeof(intListNode));
    newnode->data = x;
    newnode->link = NULL;
    return newnode;
}

//Not passing pointer of intListPointer as we are not changing the list
void print_intList(intListPointer first) {
    printf("List : ");
    while (first != NULL) {
        printf("%d -> ",first->data);
        first = first->link;
    }
    printf("\n");
}

void free_intList(intListPointer* first_p) {
    intListPointer current = *first_p;
    intListPointer next = NULL;
    while (current != NULL) {
        next = current->link;
        free(current);
        current = next;
    }
    *first_p = NULL;
    printf("List freed!\n");
}

intListPointer search_intList(intListPointer first, int x) {
    intListPointer node = first; //not necessary as we are not passing pointer
    while (node != NULL) {
        if (node->data == x) {
            return node;
        }
        node = node->link;
    }
    return NULL;
}

//Passing pointer of intListPointer (intListPointer*) as we may change the first node itself
void insert_end_intList(intListPointer* first_p, int x) {
    intListPointer newnode = NULL;
    newnode = create_intListNode(x);

    if(*first_p == NULL) {
        /*empty list insertion*/
        *first_p = newnode;
    }
    else {
        intListPointer currentnode = *first_p; //do not change first
        while (currentnode->link != NULL) {
            currentnode = currentnode->link;
        }
        currentnode->link = newnode;
    }
}


void insert_after_node_intList(intListPointer *first, intListPointer node, int val) {
    intListPointer newnode = NULL;
    newnode = create_intListNode(val);

    //check if *first exists
    if (*first) {
        //it is assumed node also exists which may be equal to first!
        newnode->link = node->link;
        node->link = newnode;
    }
    else {
        newnode->link = NULL; //taken care of in create_intListNode
        *first = newnode;
    }
}

void insert_at_beginning_intList(intListPointer *first_p, int val) {
    intListPointer newnode = create_intListNode(val);
    //intListPointer list = *first_p;
    newnode->link = *first_p;
    *first_p = newnode;
    printf("Element %d inserted at beginning!\n", val);
    print_intList(*first_p);
}

void delete_node_by_value_intList_2n(intListPointer *first_p, int val) {
    intListPointer list = *first_p;
    intListPointer tempNode = NULL;
    intListPointer targetNode = search_intList(list, val);
    if (targetNode == NULL) {
        printf("Element %d not found! Not deleting anything\n", val);
    }
    else {
        //first elem == target
        if (targetNode == *first_p) {
            tempNode = *first_p; 
            *first_p = (*first_p)->link;
            free(tempNode); tempNode = NULL; //can directly free targetNode?
        }
        else {
            for (tempNode = *first_p; tempNode->link!= targetNode; tempNode = tempNode->link);
            tempNode->link = tempNode->link->link;
            free(targetNode); targetNode = NULL;
        }
        printf("Element %d deleted!\n", val);
    }
    print_intList(*first_p);
}

//O(n) instead of O(2n)
void delete_node_by_value_intList(intListPointer *first_p, int val) {
 
    intListPointer tempNode = NULL;
    intListPointer targetNode = NULL;
    int deleted = 0;
    if (!(*first_p)) {
        printf("List empty!!");
        goto done;
    }
    if ((*first_p)->data == val) {
        targetNode = *first_p;
        *first_p = (*first_p)->link;
        free(targetNode); targetNode = NULL; deleted = 1;
        goto done;
    }
    for (tempNode = *first_p; ((tempNode->link != NULL) && (tempNode->link->data != val)); tempNode = tempNode->link);
    //note : tempNode is the trail pointer! We need to handle single node, two node and not found cases also!
    if ((tempNode->link != NULL) && tempNode->link->data == val) {
        targetNode = tempNode->link;
        tempNode->link = targetNode->link;
        free(targetNode); targetNode = NULL; deleted = 1;
        goto done;
    }


done:
    if (deleted == 1) {
        printf("Element %d deleted!\n", val);
    }
    else {
        printf("Element %d not found! Not deleting anything\n", val);
    }
    print_intList(*first_p);
}

void search_intList_driver(intListPointer list, int val) {
    intListPointer temp = NULL;
    temp = search_intList(list, val);
    if (temp != NULL) {
        printf("Get for %d successful! : %d\n",val, temp->data);
    }
    else {
        printf("Get for %d unsuccessful!\n", val);;
    }
}


void insert_after_node_intList_driver(intListPointer *first_p, int pos, int val) {
    intListPointer pos_node = NULL;
    intListPointer list = *first_p;
    pos_node = search_intList(list, pos);
    if (pos_node == NULL) {
        printf("The value %d does not exist! Hence, inserting at end of list\n", pos);
        //O(2n) if pos_node not found! needs to be optimized!
        insert_end_intList(first_p, val);
    }
    else {
        printf("The value %d exists! Hence, inserting after %d\n", pos, pos);
        insert_after_node_intList(first_p, pos_node, val);
    }
    print_intList(list);
}

void simple_int_linked_list_driver() {

    intListPointer list = NULL;
    
    int data[10] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    int i = 0, val = 0, pos = 0;
    for (i = 0; i < 10; i++) {
        insert_end_intList(&list, data[i]);
    }
    print_intList(list); nl();

    val = 21; search_intList_driver(list, val);
    val = 22; search_intList_driver(list, val); nl();

    pos = 21; val = 22; insert_after_node_intList_driver(&list, pos, val); nl();
    pos = 75; val = 144; insert_after_node_intList_driver(&list, pos, val); nl();

    //delete by node and delete by value
    val = 22; delete_node_by_value_intList_2n(&list, val); 
    val = 1; delete_node_by_value_intList_2n(&list, val); 
    val = 1; insert_at_beginning_intList(&list, val); 
    val = 100; delete_node_by_value_intList_2n(&list, val);nl();

    val = 5; delete_node_by_value_intList(&list, val);
    pos = 3; val = 5; insert_after_node_intList_driver(&list, pos, val);
    val = 1; delete_node_by_value_intList(&list, val);
    val = 1; insert_at_beginning_intList(&list, val); 
    val = 144; delete_node_by_value_intList(&list, val);
    val = 200; delete_node_by_value_intList(&list, val);nl();

    free_intList(&list);

}
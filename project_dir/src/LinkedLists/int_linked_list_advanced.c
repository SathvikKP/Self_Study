#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../utils/utils.h"
#include "linked_list.h"


void insert_non_decreasing_intList(intListPointer *first_p, int val) {

    /*  case 0: empty list
        case 1: insert at beginning
        case 2 and 3: insert at middle
        case 4: insert at end*/

    intListPointer targetNode = create_intListNode(val);
    intListPointer currentNode = NULL;
    intListPointer trailNode = NULL;
    intListPointer tempNode = NULL;

    if (*first_p == NULL) {
        *first_p = targetNode; 
        goto insertDone;
    }
    currentNode = *first_p;
    while (currentNode != NULL) {
        switch (COMPARE(targetNode->data, currentNode->data)) {
            case 1:
                //can put the trail, current assignment here also
                break;
            default:
                if (trailNode == NULL) {
                    //insert before first node
                    targetNode->link = currentNode;
                    *first_p = targetNode;
                    goto insertDone;
                }
                else {
                    //insert at any middle position
                    trailNode->link = targetNode;
                    targetNode->link = currentNode;
                    goto insertDone;
                }
        }
        trailNode = currentNode;
        currentNode = currentNode->link;
    }
    //insert at end 
    trailNode->link = targetNode;
    targetNode->link = NULL; //redundant

insertDone:
    printf("Node with value %d inserted!\n",val);
    tempNode = *first_p;
    print_intList(tempNode);

}


intListPointer merge_intList_non_decreasing(intListPointer *list1_p, intListPointer *list2_p) {
    intListPointer l1 = *list1_p;
    intListPointer l2 = *list2_p;
    intListPointer l3 = NULL;
    intListPointer newfirst = NULL;
    intListPointer temp = NULL;

    temp = *list1_p; printf("First "); print_intList(temp);
    temp = *list2_p; printf("Second "); print_intList(temp);

    if (l1 == NULL) {
        l3 = l2;
        goto done;
    }
    else if (l2 == NULL) {
        l3 = l1;
        goto done;
    }
    if ((l1->data) <= (l2->data)) {
        l3 = l1;
        l1 = l1->link;
    } else {
        l3 = l2;
        l2 = l2->link;
    }
    newfirst = l3;

    while ((l1 != NULL) && (l2 != NULL)) {
        if ((l1->data) <= (l2->data)) {
            l3->link = l1;
            l3 = l1;
            l1 = l1->link;
        }
        else {
            l3->link = l2;
            l3 = l2;
            l2 = l2->link;
        }
    }
    /*
    while(l1 != NULL) {
        l3->link = l1;
        l3 = l1; //redundant ??
        l1 = l1->link; 
    }
    while(l2 != NULL) {
        l3->link = l2;
        l3 = l2; //redundant ??
        l2 = l2->link;
    }*/
    if (l1 != NULL) {
        l3->link = l1;
    }
    else {
        l3->link = l2;
    }
done:
    *list1_p = NULL; *list2_p = NULL;
    temp = newfirst; printf("Merged "); print_intList(newfirst); nl();
    return newfirst;
}

/*

intListPointer* merge_intList_alternate(intListPointer *list1_p, intListPointer *list2_p) {
    //Logic is similar as merge_intList_non_decreasing
    //but instead of comparing data values, simply use
    //a flag to merge the left and right list values.
}

*/

void invert_intList(intListPointer* first_p) {
    
    /*
    intListPointer current = *first_p;
    intListPointer next = NULL, trail = NULL;

    if (current == NULL || current->link == NULL) {
        //0 or 1 nodes
        return;
    }
    next = current->link;
    while (next != NULL) {
        current->link = trail;
        trail = current; //update trail
        current = next; //update current
        next = current->link; //update next
    }
    current->link = trail;
    *first_p = current;

    */

    intListPointer lead = *first_p;
    intListPointer middle = NULL, trail = NULL;
    while (lead) {
        trail = middle;
        middle = lead;
        lead = lead->link;
        middle->link = trail;
    }
    *first_p = middle;
    printf("List inverted!\n");

}

void int_linked_list_advanced_driver() {

    intListPointer list1 = NULL, list2 = NULL, list3 = NULL;
    int data1[6] = {7, 3, 5, 1, 9, 11};
    int data2[8] = {8, 4, 6, 10, 2, 8, 10, 12};
    int i = 0;
    for (i = 0; i < 6; i++) {
        insert_non_decreasing_intList(&list1, data1[i]);
    }
    for (i = 0; i < 8; i++) {
        insert_non_decreasing_intList(&list2, data2[i]);
    }
    
    nl(); print_intList(list1); 
    print_intList(list2); nl();

    list3 = merge_intList_non_decreasing(&list1, &list2);
    print_intList(list3); nl();

    invert_intList(&list3);
    print_intList(list3); nl();

    free_intList(&list3);
    //free_intList(&list1);
    //free_intList(&list2);

}
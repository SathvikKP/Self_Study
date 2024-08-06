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

void ll_sparse_matrix_enc_transpose(sparseMatrixPointerLL *A, sparseMatrixPointerLL *B) {

    if (*B != NULL) {
        printf("\nTranspose matrix pointer is not NULL!\n"); return;
    }

    MALLOC(B, sizeof(sparseMatrixLL)); mallocCount++;

    int i = 0, j = 0, numHeads = 0, currentRow = 0;

    matrixPointer nodeA = (*A)->node;
    int rowsA = nodeA->u.entry.row;;
    int colsA = nodeA->u.entry.col;
    int numTerms = nodeA->u.entry.value;

    matrixPointer tempA = NULL, headA = NULL, prevA = NULL;
    matrixPointer tempB = NULL, headB = NULL, prevB = NULL, lastB = NULL;

    int rowsB = colsA; int colsB = rowsA;

    /*Create the matrix node containing meta data*/
    matrixPointer nodeB = ll_create_sparse_matrix_node_enc(); mallocCount++;
    nodeB->tag = entry;
    nodeB->u.entry.row = rowsB; nodeB->u.entry.col = colsB; nodeB->u.entry.value = numTerms;

    (*B)->node = nodeB;
    numHeads = (rowsB > colsB) ? rowsB : colsB;

    if (!numHeads) {
        nodeB->right = nodeB;
        printf("\nTranspose Matrix created with no dimensions!\n");
        return;
    }

    for (i = 0; i < numHeads; i++) {
        tempB = ll_create_sparse_matrix_node_enc(); mallocCount++;
        tempB->tag = head;
        tempB->right = tempB; //we will link headers later (cannot link if all nodes not created yet)
        tempB->u.next = tempB;
        (*B)->headNode[i] = tempB;
    }

    /*Traverse A columnwise using down pointer, assign to B->headNode[j] rowwise*/
    /*For better understanding, refer the print matrix and read matrix functions!*/

    headA = nodeA->right;
    prevA = NULL;

    headB = nodeB->right;
    prevB = NULL;

    currentRow = 0; lastB = (*B)->headNode[0];

    for (i = 0; i < nodeA->u.entry.col; i++) {
        /*for each column, ex : h[0], go down and for each node, attach to B*/
        for (tempA = headA->down; tempA != headA; tempA = tempA->down) {

            if (tempA->u.entry.col > currentRow) {
                lastB->right = (*B)->headNode[currentRow]; //link old row back to headernode
                currentRow = tempA->u.entry.col; //update currentRow
                lastB = (*B)->headNode[tempA->u.entry.col]; //or updated currentRow
            }
            
            tempB = ll_create_sparse_matrix_node_enc(); mallocCount++;
            tempB->tag = entry;
            tempB->u.entry.row = tempA->u.entry.col; //swap
            tempB->u.entry.col = tempA->u.entry.row; //swap
            tempB->u.entry.value = tempA->u.entry.value; //asign

            //link the new node to rowlist of B
            lastB->right = tempB;
            lastB =tempB;

            //link the new node to columnlist of B
            (*B)->headNode[tempB->u.entry.col]->u.next->down = tempB;
            (*B)->headNode[tempB->u.entry.col]->u.next = tempB;

        }
        /*After traversing column of A, go to next column*/
        headA = headA->u.next;
    }
    /*Close the row lists!*/
    lastB->right = (*B)->headNode[currentRow];

    /*Close column lists*/
    for (i = 0; i < nodeB->u.entry.col; i++) {
        (*B)->headNode[i]->u.next->down = (*B)->headNode[i];
    }
}

void linked_list_sparse_matrix_advanced_driver() {

}
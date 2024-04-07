#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../utils/utils.h"
#include "linked_list.h"

#define MAX_SPARSE_MATRIX_SIZE 50

int mallocCount = 0;
int freeCount = 0;

/*header node array of matrix!*/
matrixPointer headNode[MAX_SPARSE_MATRIX_SIZE];

matrixPointer ll_create_sparse_matrix_node() {
    matrixPointer node = NULL;
    MALLOC(node, sizeof(matrixNode));
    node->down = NULL;
    node->right = NULL;
    return node;
}

matrixPointer ll_read_sparse_matrix(char* filename) {

    /*Variables*/
    int inputRows = 0, inputCols = 0;
    int i = 0, row = 0, col = 0, value = 0, currentRow = 0;
    int numRows = 0, numCols = 0, numTerms = 0, numHeads = 0;
    int **inputMatrix = NULL;
    matrixPointer temp, last, node;

    /*Read from file and get the data*/
    /*  Data is assumed to be provided in proper order :
        1. non decreasing row-wise followed by col-wise co-ords!
        2. Matrix is 0-indexed, i.e (0,0) --> (MAX_SIZE-1, MAX_SIZE-1)*/
    inputMatrix = read_2d_array_from_file(filename, &inputRows, &inputCols); mallocCount++;
    //print2Darray_p(inputMatrix, inputRows, inputCols);
    
    /*Matrix meta deta from first row*/
    numRows = inputMatrix[0][0]; numCols = inputMatrix[0][1]; numTerms = inputMatrix[0][2];
    numHeads = (numRows > numCols) ? numRows : numCols;

    /*Set up the header node for list of header nodes*/
    node = ll_create_sparse_matrix_node(); mallocCount++;
    /*Matrix meta data to the header node*/
    node->tag = entry;
    node->u.entry.row = numRows; node->u.entry.col = numCols; node->u.entry.value = numTerms;
    /*Initialize header nodes*/
    if (!numHeads) {
        node->right = node; //no elements case, point to itself!
    } else {
        /*Create header nodes*/
        for (i = 0; i < numHeads; i++) {
            temp = ll_create_sparse_matrix_node(); mallocCount++;
            headNode[i] = temp; //assign new node to headNode[i]
            headNode[i]->tag = head; //mark as head
            headNode[i]->right= temp; //we use the right to point to itself (if it is not used)
            headNode[i]->u.next = temp; //we will link all header nodes at the end
            //u.next points to itself here. We will later use this to point to the last column node
        }

        currentRow = 0; //to add elements row-wise, we maintain currentRow
        last = headNode[0]; //we will maintain last to attach to end of row list

        /*Read based on numTerms*/
        for (i = 1; i <= numTerms; i++) { //note the initial value of i
            
            row = inputMatrix[i][0]; col = inputMatrix[i][1]; value = inputMatrix[i][2];

            if (row > currentRow) { //close the current row!
                last->right = headNode[currentRow]; //link the right field (rowWise) to the new element
                currentRow = row; last = headNode[row]; //update the currentRow and last values
            }
            temp = ll_create_sparse_matrix_node(); mallocCount++; //Create a node to add the entry
            temp->tag = entry; // mark as entry node and populate the entryNode values
            temp->u.entry.row = row; temp->u.entry.col = col; temp->u.entry.value = value;

            last->right = temp; //link to row list
            last = temp; //mark newly added node as last

            /*  Now, we can link to the column list. But we need to be careful as we are
                not inserting columnwise in order, hence, we use the u.next
                field (which stores the last node in the column list)
                and then use the down pointer of that node to link the newly created node*/

            headNode[col]->u.next->down = temp; 
            headNode[col]->u.next = temp;
        }

        /*Close the rows by completing circular lists*/
        last->right = headNode[currentRow];
        /*Close column lists*/
        for (i = 0; i < numCols; i++) {
            headNode[i]->u.next->down = headNode[i];
        }
        /*Link header nodes together (the u.next is no longer required for maintaining)
        the temporary last column pointers!*/
        for (i = 0; i < numHeads-1; i++) {
            headNode[i]->u.next = headNode[i+1];
        }
        headNode[numHeads-1]->u.next = node;
        node->right = headNode[0];
    }

    free2Darray(inputMatrix, inputRows, inputCols); freeCount++;
    return node;

}

void linked_list_sparse_matrix_driver() {

    char mat1file[] = "./src/LinkedLists/inputs/sparse_matrix1.txt";
    matrixPointer mat1 = ll_read_sparse_matrix(mat1file);
}








/*

Notes : ll_read_sparse_matrix explanation of linking

Source : TABNINE AI

In the ll_read_sparse_matrix function, the way nodes are linked to the row and column lists 
reflects the structure and traversal logic of the sparse matrix implemented as a linked list. 
Let's break down the reasoning behind using different pointers for row and column linking:


Row Lists Linking (using `right` pointer)

The sparse matrix is primarily processed row-wise, as indicated by the loop that iterates
through each term (non-zero element) based on the number of terms (numTerms).

For each term, a new node is created and added to the end of the current row list. This is 
achieved by setting the right pointer of the last node in the row (last->right = temp;). The
right pointer is used for horizontal traversal, effectively linking all nodes within the same
row.

When moving to a new row, the last node of the current row is linked back to the head of
the row, creating a circular list for that row. This circular linking is also done using 
the right pointer (last->right = headNode[currentRow];).


Column Lists Linking (using `u.next->down` pointer)
The column lists are not built by direct sequential insertion as the row lists are. 
Instead, nodes are inserted into the appropriate column list based on their column index,
which is determined after the row-wise insertion.

Each head node for the columns (and rows, if they are more) is initially linked to itself
via the u.next pointer, which is intended to serve as a temporary pointer to keep track of
the last node in the column list during the construction of the matrix.

When a new node is added to a column, it is linked to the column list by setting the down
pointer of the last node in the column (headNode[col]->u.next->down = temp;). This down 
pointer is used for vertical traversal, linking nodes within the same column.

The u.next pointer of the column head node is then updated to point to this newly added
node (headNode[col]->u.next = temp;), ensuring that u.next always points to the last node in
the column list, ready for the next insertion.


This dual mechanism of linking (using right for rows and u.next->down for columns) 
allows the function to efficiently construct the sparse matrix in a way that supports
both row-wise and column-wise traversal, despite the row-major order of insertion. 
It leverages the flexibility of the linked list structure to maintain separate lists
for rows and columns within the same data structure, facilitating operations that may 
require accessing elements by row or column.


*/
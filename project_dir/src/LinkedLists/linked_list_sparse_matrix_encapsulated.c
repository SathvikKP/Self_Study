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

/*header node array of matrix!*/
//matrixPointer headNode[MAX_SPARSE_MATRIX_SIZE];

matrixPointer ll_create_sparse_matrix_node_enc() {
    matrixPointer node = NULL;
    MALLOC(node, sizeof(matrixNode));
    node->down = NULL;
    node->right = NULL;
    return node;
}

sparseMatrixPointerLL ll_read_sparse_matrix_enc(char* filename) {

    sparseMatrixPointerLL mat = NULL;
    MALLOC(mat, sizeof(sparseMatrixLL)); mallocCount++;

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
    node = ll_create_sparse_matrix_node_enc(); mallocCount++;
    /*Matrix meta data to the header node*/
    node->tag = entry;
    node->u.entry.row = numRows; node->u.entry.col = numCols; node->u.entry.value = numTerms;
    /*Initialize header nodes*/
    if (!numHeads) {
        node->right = node; //no elements case, point to itself!
    } else {
        /*Create header nodes*/
        for (i = 0; i < numHeads; i++) {
            temp = ll_create_sparse_matrix_node_enc(); mallocCount++;
            mat->headNode[i] = temp; //assign new node to headNode[i]
            mat->headNode[i]->tag = head; //mark as head
            mat->headNode[i]->right= temp; //we use the right to point to itself (if it is not used)
            mat->headNode[i]->u.next = temp; //we will link all header nodes at the end
            //u.next points to itself here. We will later use this to point to the last column node
        }

        currentRow = 0; //to add elements row-wise, we maintain currentRow
        last = mat->headNode[0]; //we will maintain last to attach to end of row list

        /*Read based on numTerms*/
        for (i = 1; i <= numTerms; i++) { //note the initial value of i
            
            row = inputMatrix[i][0]; col = inputMatrix[i][1]; value = inputMatrix[i][2];

            if (row > currentRow) { //close the current row!
                last->right = mat->headNode[currentRow]; //link the right field (rowWise) to the header node
                currentRow = row; last = mat->headNode[row]; //update the currentRow and last values
            }
            temp = ll_create_sparse_matrix_node_enc(); mallocCount++; //Create a node to add the entry
            temp->tag = entry; // mark as entry node and populate the entryNode values
            temp->u.entry.row = row; temp->u.entry.col = col; temp->u.entry.value = value;

            last->right = temp; //link to row list
            last = temp; //mark newly added node as last

            /*  Now, we can link to the column list. But we need to be careful as we are
                not inserting columnwise in order, hence, we use the u.next
                field (which stores the last node in the column list)
                and then use the down pointer of that node to link the newly created node*/

            mat->headNode[col]->u.next->down = temp; 
            mat->headNode[col]->u.next = temp;
        }

        /*Close the rows by completing circular lists*/
        last->right = mat->headNode[currentRow];
        /*Close column lists*/
        for (i = 0; i < numCols; i++) {
            mat->headNode[i]->u.next->down = mat->headNode[i];
        }
        /*Link header nodes together (the u.next is no longer required for maintaining)
        the temporary last column pointers!*/
        for (i = 0; i < numHeads-1; i++) {
            mat->headNode[i]->u.next = mat->headNode[i+1];
        }
        mat->headNode[numHeads-1]->u.next = node;
        node->right = mat->headNode[0];
    }

    free2Darray(inputMatrix, inputRows, inputCols); freeCount++;
    printf("\nMatrix Created!\n");
    mat->node = node;
    return mat;

}


void ll_print_sparse_matrix_enc(sparseMatrixPointerLL mat) {

    if (mat == NULL || mat->node == NULL) {
        printf("\nMatrix is NULL!\n");
        return;
    }
    /*Print in row major form*/
    matrixPointer node = mat->node;
    int i = 0;
    matrixPointer temp = NULL;
    matrixPointer head = node->right; //headNode[0]
    /*Print matrix dimentions*/
    printf("\nnumRows = %d, numCols = %d, numTerms = %d\n", 
        node->u.entry.row, node->u.entry.col, node->u.entry.value);
    /*print row wise*/
    for (i = 0; i < node->u.entry.row; i++) {
        /*for each row, ex : h[0], go right and print if exists*/
        for (temp = head->right; temp != head; temp = temp->right) {
            printf("%5d%5d%5d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
        }
        /*After printing a row, go to next row*/
        head = head->u.next;
    }
    nl();
}

void ll_erase_sparse_matrix_enc(sparseMatrixPointerLL *mat_p) {

    if (mat_p == NULL || *mat_p == NULL) {
        printf("\nMatrix pointer is NULL. Nothing to erase.\n");
        return;
    }
    matrixPointer node = (*mat_p)->node;
    int i = 0;
    matrixPointer temp = NULL;
    matrixPointer delNode = NULL;
    matrixPointer head = (node)->right; //headNode[0]

    /*Free entry nodes*/
    for (i = 0; i < (node)->u.entry.row; i++) {
        temp = head->right;
        while (temp != head) {
            delNode = temp;
            temp = temp->right;
            if (delNode) {
                free(delNode); delNode = NULL; freeCount++;
            }
        }
        head = head->u.next; 
        //We can delete header nodes here also to further optimize!!
        /*
            delNode = head; head = head->u.next; free(delNode);
        */
    }
    /*Free header nodes*/
    head = (node)->right; //not necessary if we delete heads in previous step
    temp = head;
    while(temp != (node)) {
        delNode = temp;
        temp = temp->u.next;
        if (delNode) {
            free(delNode); delNode = NULL; freeCount++;
        }
    }
    free(node); node = NULL; freeCount++;
    free(*mat_p); *mat_p = NULL; freeCount++;
    printf("\nMatrix Erased!\n");
 }

void ll_insert_node_to_sparse_matrix_enc(sparseMatrixPointerLL *mat_p, int row, int col, int value) {

    matrixPointer node = (*mat_p)->node;

    int i = 0, skipCol = FALSE, rowDone = FALSE, colDone = FALSE; //skipCol not needed!
    matrixPointer newNode = NULL;
    matrixPointer head = node->right; //headNode[0] //for traversal rowwise!
    matrixPointer temp = NULL;
    matrixPointer prev = NULL;

    if ((row >= node->u.entry.row) || (col >= node->u.entry.col)) {
        printf("\nInvalid co-ordinates! Out of bounds! Not inserting\n");
        return;
    }
    
    /*Traverse to headNode[row]*/
    for (i = 0; i < row; i++) {
        head = head->u.next;
    }
    temp = head->right;
    /*Compare columns*/
    while ((temp != head) && (rowDone == FALSE)) {
        switch (COMPARE(temp->u.entry.col, col)) {
            case -1 :
                /*Current node's col value is less, so continue*/
                break;
            case 0 :
                /*Co-ord already exists!*/
                printf("Insertion : Replacing existing value \n");
                temp->u.entry.value = value; rowDone = TRUE; colDone = TRUE; skipCol = TRUE;
                break;
            case 1 :
                /*  We have overshoot the node to insert
                    Cases to consider: 
                        1. No entry nodes in the row (handled later?)
                        2. insert at beginning
                        3. insert at middle
                        4. insert at end (same as case 1??)
                */
                newNode = ll_create_sparse_matrix_node_enc(); mallocCount++;
                newNode->tag = entry; 
                newNode->u.entry.row = row; newNode->u.entry.col = col; newNode->u.entry.value = value;
                if (prev == NULL) {
                    /*Insert at beginning of row*/
                    head->right = newNode; newNode->right = temp;
                } else {
                    /*Insert at middle of row*/
                    prev->right = newNode; newNode->right = temp;
                }
                rowDone = TRUE;
                break;
            default:
                fprintf(stderr, "\nUnreacheable code ERROR\n"); exit(EXIT_FAILURE);
        }
        prev = temp;
        temp = temp->right;
    } /*while*/

    if ((rowDone == FALSE) && (temp == head)) {
        /*We need to insert to an empty rowlist or end of rowlist determined by prev*/
        newNode = ll_create_sparse_matrix_node_enc(); mallocCount++;
        newNode->tag = entry; 
        newNode->u.entry.row = row; newNode->u.entry.col = col; newNode->u.entry.value = value;
        if (prev == NULL) {
            /*Insert at beginning of empty row*/
            head->right = newNode; newNode->right = head; //or temp
        } else {
            /*Insert at end of row*/
            prev->right = newNode; newNode->right = head; //or temp
        }
        rowDone = TRUE;
    }

    /*Now that we are done linking rowwise, we can link columnwise*/

    if (skipCol == FALSE) {

        head = node->right;
        /*Traverse to headNode[col]*/
        for (i = 0; i < col; i++) {
            head = head->u.next;
        }
        temp = head->down;
        prev = NULL;
        /*Compare rows*/
        while ((temp != head) && (colDone == FALSE)) {
            switch (COMPARE(temp->u.entry.row, row)) {
                case -1 :
                    /*Current node's row value is less, so continue*/
                    break;                    
                case 1 :
                    /*  We have overshoot the node to insert
                        Cases to consider: 
                            1. No entry nodes in the col (handled later?)
                            2. insert at beginning
                            3. insert at middle
                            4. insert at end (same as case 1??)
                    */
                    if (prev == NULL) {
                        /*Insert at beginning of col*/
                        head->down = newNode; newNode->down = temp;
                    } else {
                        /*Insert at middle of col*/
                        prev->down = newNode; newNode->down = temp;
                    }
                    colDone = TRUE;
                    break;
                case 0:
                    fprintf(stderr, "\nSomething seriously wrong!!\n"); exit(EXIT_FAILURE);
                default:
                    fprintf(stderr, "\nUnreacheable code ERROR!\n"); exit(EXIT_FAILURE);
            }
            prev = temp;
            temp = temp->down;
        } /*while*/
        if ((colDone == FALSE) && (temp == head)) {
            /*We need to insert to an empty collist or end of collist determined by prev*/
            if (prev == NULL) {
                /*Insert at beginning of empty col*/
                head->down = newNode; newNode->down = head; //or temp
            } else {
                /*Insert at end of col*/
                prev->down = newNode; newNode->down = head; //or temp
            }
            colDone = TRUE;
        }

        /*  Only iff when we insert a new node i.e, skipCol == FALSE
            We need to update matrix metaData --> u.entry.value*/
        node->u.entry.value++;

    }
    if ((rowDone == FALSE) || (colDone == FALSE)) {
        printf("\nrowDone = %d colDone = %d\n", rowDone, colDone);
        fprintf(stderr, "\nLinking of nodes not properly done!! Serious Error!\n"); exit(EXIT_FAILURE);
    }
    else {
        printf("\nInsertion : Done\n");
    }

}



void ll_delete_node_from_sparse_matrix_enc(sparseMatrixPointerLL *mat_p, int row, int col) {

    matrixPointer node = (*mat_p)->node;

    int i = 0, rowDone = FALSE, colDone = FALSE, notFound = FALSE; 
    matrixPointer delNode = NULL;
    matrixPointer head = node->right; //headNode[0] //for traversal
    matrixPointer temp = NULL;
    matrixPointer prev = NULL;

    if ((row >= node->u.entry.row) || (col >= node->u.entry.col)) {
        /*(row, col) out of bounds*/
        printf("\nInvalid co-ordinates! Out of bounds! Not deleting\n"); return;
    }

    for (i = 0; i < row; i++) {
        head = head->u.next;
    }
    temp = head->right;
    while ((temp != head) && (rowDone == FALSE) && (notFound == FALSE)) {
        switch (COMPARE(temp->u.entry.col, col)) {
            case -1 :
                /*Current node's col value is less, so continue*/
                break;     
            case 0 :
                /*node to delete found!*/
                delNode = temp; //mark to delete later
                if (prev == NULL) {
                    /*Delete from beginning of row*/
                    head->right = temp->right; //relink row list
                    temp->right = NULL; //not necessary
                } else {
                    /*Delete from middle or end of row*/
                    prev->right = temp->right; //relink row list
                    temp->right = NULL; //not necessary
                }
                rowDone = TRUE;
                break;           
            case 1 :
                /*  We have overshoot the node to delete which means
                    node does not exist!*/
                notFound = TRUE;
                break;
            default:
                fprintf(stderr, "\nUnreachable code error!\n"); exit(EXIT_FAILURE);
        } //end switch
        prev = temp;
        temp = temp->right;
    } //end while
    if (notFound == TRUE || rowDone == FALSE) {
        /*(row, col) do not exist, return*/
        printf("\nInvalid co-ordinates! Node does not exist! Not deleting\n"); return;
    }
    
    /*Suppose we de-linked from rowlist, we need to delink from column list also*/
    head = node->right; //headNode[0] //for traversal
    temp = NULL;
    prev = NULL;
    for (i = 0; i < col; i++) {
        head = head->u.next;
    }
    temp = head->down;
    prev = NULL;
    while ((temp!= head) && (colDone == FALSE)) {
        switch (COMPARE(temp->u.entry.row, row)) {
            case -1 :
                /*Current node's row value is less, so continue*/
                break;     
            case 0 :
                /*node to delete found!*/
                //delNode = temp; //mark to delete later
                if (prev == NULL) {
                    /*Delete from beginning of col*/
                    head->down = temp->down; //relink col list
                    temp->down = NULL; //not necessary
                } else {
                    /*Delete from middle or end of col*/
                    prev->down = temp->down; //relink col list
                    temp->down = NULL; //not necessary
                }
                colDone = TRUE;
                break;           
            case 1 :
                /*  We have overshoot the node to delete*/
                /* Code should not reach here as row,col exists!*/
                fprintf(stderr, "\nSomething seriously wrong with the column list! (1)\n");
                exit(EXIT_FAILURE);
            default:
                fprintf(stderr, "\nUnreachable code error!\n"); exit(EXIT_FAILURE);
        }
        prev = temp;
        temp = temp->down;
    }//end while
    if ((colDone == FALSE) || (temp == head)) { //temp == head not needed
        fprintf(stderr, "\nSomething seriously wrong with the column list! (2)\n"); exit(EXIT_FAILURE);
    }

    /*we have delinked from both lists, now we can free*/
    if (delNode) {
        printf("\nDeleted node at row = %d, col = %d with value %d\n",
            delNode->u.entry.row, delNode->u.entry.col, delNode->u.entry.value);
        free(delNode); delNode = NULL; freeCount++;
    }

    /*Update matrix metadata (numTerms)*/
    node->u.entry.value--;
}



 /*
 Create functions to
 1. insert a value to existing matrix
 2. delete a value from existing matrix if exists
 3. Add 2 matrices
 4. Calculate transpose
 5. Multiply 2 matrices
 6. Copy a matix
 */


void ll_insert_node_to_sparse_matrix_enc_test_function();
void ll_delete_node_from_sparse_matrix_enc_test_function();

void linked_list_sparse_matrix_encapsulated_driver() {

    char mat1file[] = "./src/LinkedLists/inputs/sparse_matrix3.txt";
    char mat2file[] = "./src/LinkedLists/inputs/sparse_matrix2.txt";

    mallocCount = 0; freeCount = 0;

    sparseMatrixPointerLL mat1 = ll_read_sparse_matrix_enc(mat1file);
    sparseMatrixPointerLL mat2 = ll_read_sparse_matrix_enc(mat2file);
    ll_print_sparse_matrix_enc(mat1); ll_print_sparse_matrix_enc(mat2);
    ll_erase_sparse_matrix_enc(&mat1); ll_erase_sparse_matrix_enc(&mat2);

    ll_insert_node_to_sparse_matrix_enc_test_function();
    ll_delete_node_from_sparse_matrix_enc_test_function();

    if (mallocCount == freeCount) {
        printf("\nAll memory freed successfully!\n");
        printf("mallocCount: %d freeCount: %d\n", mallocCount, freeCount);
    } else {
        printf("\nMemory leak detected!\n");
        printf("mallocCount: %d freeCount: %d\n", mallocCount, freeCount);
    } 

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


void ll_insert_node_to_sparse_matrix_enc_test_function() {

    
    char matfile[] = "./src/LinkedLists/inputs/sparse_matrix3.txt";

    sparseMatrixPointerLL tc1 = ll_read_sparse_matrix_enc(matfile);
    printf("Test Case 1: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc1);
    printf("\nInserting a New Node at (2, 1) in an Empty Row\n");
    ll_insert_node_to_sparse_matrix_enc(&tc1, 2, 1, 5); //Inserting a New Node in an Empty Row
    ll_print_sparse_matrix_enc(tc1); ll_erase_sparse_matrix_enc(&tc1);

    sparseMatrixPointerLL tc2 = ll_read_sparse_matrix_enc(matfile);
    printf("Test Case 2: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc2);
    printf("\nInserting a New Node at (3, 1) in non Empty Row\n");
    ll_insert_node_to_sparse_matrix_enc(&tc2, 3, 1, 7); //Inserting a New Node in a Non-Empty Row
    ll_print_sparse_matrix_enc(tc2); ll_erase_sparse_matrix_enc(&tc2);

    sparseMatrixPointerLL tc3 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 3: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc3);
    printf("\nInserting a New Node at (1, 4) at End of Row\n");
    ll_insert_node_to_sparse_matrix_enc(&tc3, 1, 4, 2); //Inserting a Node at the End of a Row
    ll_print_sparse_matrix_enc(tc3); ll_erase_sparse_matrix_enc(&tc3);
    
    sparseMatrixPointerLL tc4 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 4: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc4);
    printf("\nInserting a New Node at (4, 0) at the Beginning of a Row\n");
    ll_insert_node_to_sparse_matrix_enc(&tc4, 4, 0, 5); //Inserting a Node at the Beginning of a Row
    ll_print_sparse_matrix_enc(tc4); ll_erase_sparse_matrix_enc(&tc4);
    
    sparseMatrixPointerLL tc5 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 5: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc5);
    printf("\nInserting a New Node at (0, 1) in an Empty Column\n");
    ll_insert_node_to_sparse_matrix_enc(&tc5, 0, 1, 3); //Inserting a Node in a an Empty Column
    ll_print_sparse_matrix_enc(tc5); ll_erase_sparse_matrix_enc(&tc5);

    sparseMatrixPointerLL tc6 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 6: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc6);
    printf("\nInserting a New Node at (2, 3) in a Non-Empty Column\n");
    ll_insert_node_to_sparse_matrix_enc(&tc6, 2, 3, 7); //Inserting a New Node in a Non-Empty Column
    ll_print_sparse_matrix_enc(tc6); ll_erase_sparse_matrix_enc(&tc6);

    sparseMatrixPointerLL tc7 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 7: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc7);
    printf("\nInserting a New Node at (0, 3) at the Beginning of a Non-Empty Column\n");
    ll_insert_node_to_sparse_matrix_enc(&tc7, 0, 3, 8); //Inserting a Node at the Beginning of a Non-Empty Column
    ll_print_sparse_matrix_enc(tc7); ll_erase_sparse_matrix_enc(&tc7);

    sparseMatrixPointerLL tc8 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 8: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc8);
    printf("\nInserting a New Node at (4, 0) at the End of a Column\n");
    ll_insert_node_to_sparse_matrix_enc(&tc8, 4, 0, 9); //Inserting a Node at the End of a Column
    ll_print_sparse_matrix_enc(tc8); ll_erase_sparse_matrix_enc(&tc8);

    sparseMatrixPointerLL tc9 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 9: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc9);
    printf("\nInserting a New Node at (1, 0) - Updating an Existing Node\n");
    ll_insert_node_to_sparse_matrix_enc(&tc9, 1, 0, 9); //Updating an Existing Node
    ll_print_sparse_matrix_enc(tc9); ll_erase_sparse_matrix_enc(&tc9);

    //Multiple insertions

    sparseMatrixPointerLL tc10 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 10: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc10);
    printf("\nInserting Multiple nodes at (0, 2), (1, 2) and (2, 2) \n");
    ll_insert_node_to_sparse_matrix_enc(&tc10, 0, 2, 3);
    ll_insert_node_to_sparse_matrix_enc(&tc10, 1, 2, 4);
    ll_insert_node_to_sparse_matrix_enc(&tc10, 2, 2, 5);
    ll_print_sparse_matrix_enc(tc10); ll_erase_sparse_matrix_enc(&tc10);

    sparseMatrixPointerLL tc11 = ll_read_sparse_matrix_enc(matfile); 
    printf("Test Case 11: Initial Matrix:\n"); ll_print_sparse_matrix_enc(tc11);
    printf("\nInserting a New Node at (5, 5) i.e Invalid Coordinates\n");
    ll_insert_node_to_sparse_matrix_enc(&tc11, 5, 5, 10); //Inserting a Node with Invalid Coordinates
    ll_print_sparse_matrix_enc(tc11); ll_erase_sparse_matrix_enc(&tc11);

}


void ll_delete_node_from_sparse_matrix_enc_test_function() {
    char matfile[] = "./src/LinkedLists/inputs/sparse_matrix3.txt";

    // Test Case 1: Deleting an existing node (middle of a row)
    sparseMatrixPointerLL mat1 = ll_read_sparse_matrix_enc(matfile);
    printf("Test Case 1: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat1);
    printf("\nDeleting node at (1, 3) - Middle of a row:\n");
    ll_delete_node_from_sparse_matrix_enc(&mat1, 1, 3); 
    ll_print_sparse_matrix_enc(mat1); ll_erase_sparse_matrix_enc(&mat1);

    // Test Case 2: Deleting an existing node (start of a row)
    sparseMatrixPointerLL mat2 = ll_read_sparse_matrix_enc(matfile);
    printf("\nTest Case 2: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat2);
    printf("\nDeleting node at (1, 0) - Start of a row:\n");
    ll_delete_node_from_sparse_matrix_enc(&mat2, 1, 0);
    ll_print_sparse_matrix_enc(mat2); ll_erase_sparse_matrix_enc(&mat2);

    // Test Case 3: Deleting a node that does not exist
    sparseMatrixPointerLL mat3 = ll_read_sparse_matrix_enc(matfile);
    printf("\nTest Case 3: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat3);
    printf("\nAttempting to delete a non-existing node at (2, 2):\n");
    ll_delete_node_from_sparse_matrix_enc(&mat3, 2, 2);
    ll_print_sparse_matrix_enc(mat3); ll_erase_sparse_matrix_enc(&mat3);

    // Test Case 4: Deleting an existing node (end of a row)
    sparseMatrixPointerLL mat4 = ll_read_sparse_matrix_enc(matfile);
    printf("\nTest Case 4: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat4);
    printf("\nDeleting node at (4, 2) - End of a row:\n");
    ll_delete_node_from_sparse_matrix_enc(&mat4, 4, 2);
    ll_print_sparse_matrix_enc(mat4); ll_erase_sparse_matrix_enc(&mat4);

    // Test Case 5: Deleting an existing node (start of a column)
    sparseMatrixPointerLL mat5 = ll_read_sparse_matrix_enc(matfile);
    printf("\nTest Case 5: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat5);
    printf("\nDeleting node at (0, 0) - Start of a column:\n");
    ll_delete_node_from_sparse_matrix_enc(&mat5, 0, 0);
    ll_print_sparse_matrix_enc(mat5); ll_erase_sparse_matrix_enc(&mat5);

    // Test Case 6: Deleting an existing node (middle of a column)
    sparseMatrixPointerLL mat6 = ll_read_sparse_matrix_enc(matfile);
    printf("\nTest Case 6: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat6);
    printf("\nDeleting node at (1, 0) - Middle of a column:\n");
    ll_delete_node_from_sparse_matrix_enc(&mat6, 1, 0);
    ll_print_sparse_matrix_enc(mat6); ll_erase_sparse_matrix_enc(&mat6);

    // Test Case 7: Deleting a node with invalid coordinates (out of bounds)
    sparseMatrixPointerLL mat7 = ll_read_sparse_matrix_enc(matfile);
    printf("\nTest Case 7: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat7);
    printf("\nAttempting to delete a node with out-of-bounds coordinates (5, 6):\n");
    ll_delete_node_from_sparse_matrix_enc(&mat7, 5, 6);
    ll_print_sparse_matrix_enc(mat7); ll_erase_sparse_matrix_enc(&mat7);

    // Test Case 8: Multiple Deletions
    sparseMatrixPointerLL mat8 = ll_read_sparse_matrix_enc(matfile);
    printf("\nTest Case 8: Initial Matrix:\n"); ll_print_sparse_matrix_enc(mat8);
    printf("\nMultiple deletes : (1, 0):\n");
    ll_delete_node_from_sparse_matrix_enc(&mat8, 1, 0); ll_print_sparse_matrix_enc(mat8);
    printf("\nMultiple deletes : (3, 3), (3, 0), (0, 0):\n");
    ll_delete_node_from_sparse_matrix_enc(&mat8, 3, 3);
    ll_delete_node_from_sparse_matrix_enc(&mat8, 3, 0);
    ll_delete_node_from_sparse_matrix_enc(&mat8, 0, 0); ll_print_sparse_matrix_enc(mat8);
    printf("\nRemaining deletes : (1, 3), (4, 2):\n");
    ll_delete_node_from_sparse_matrix_enc(&mat8, 1, 3);
    ll_delete_node_from_sparse_matrix_enc(&mat8, 4, 2); ll_print_sparse_matrix_enc(mat8);
    ll_erase_sparse_matrix_enc(&mat8);

}


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "utils.h"

#define TRUE 1
#define FALSE 0

/*maze details*/
char file_name[32] = "inputs/maze_array.txt";
//char file_name[32] = "inputs/simple_maze.txt";
int** maze = NULL; /*maze array read from input file*/
int** mark = NULL; /*mark array used to mark if position visited*/
int rows = 0; 
int cols = 0;
int start_x = 0;
int start_y = 0;
int end_x = 0; 
int end_y = 0;
int found = FALSE;

/*utilities details*/
struct offset {
    short int horiz;
    short int vert;
};
typedef struct offset offset;

offset move[8];

struct mazeElement {
    short int row;
    short int col;
    short int dir;
};
typedef struct mazeElement mazeElement;

/*Declare stack as dynamic -> rows*cols */
mazeElement* mazeStack = NULL;
int maze_top = -1;

/*Stack function declarations*/
void printMazeStack();
void mazeStackFull();
mazeElement mazeStackEmpty(); 
void mazeStackPush(mazeElement item);
mazeElement mazeStackPop();

/*other function declarations*/
void printMaze(int** maze, int rows, int cols);
void init_move_array();
int is_valid_pos(int x, int y); 

void find_path() {
    int currentRow = 0, currentCol = 0, nextRow = 0, nextCol = 0, currentDir = 0, nextDir = 0;
    int i = 0, j = 0;
    mazeElement position;
    position.row = start_x; position.col = start_y; position.dir = 0;
    mazeStackPush(position);

    while( (maze_top > -1) && (found == FALSE) ) {
        position = mazeStackPop();
        currentRow = position.row; 
        currentCol = position.col;
        currentDir = position.dir;

        while (currentDir < 8 && (found == FALSE)) {
            
            nextRow = currentRow + move[currentDir].vert;
            nextCol = currentCol + move[currentDir].horiz;
            if (is_valid_pos(nextRow, nextCol)) {
                if (nextRow == end_x && nextCol == end_y) {
                    found = TRUE;
                }
                else if (mark[nextRow][nextCol] == 0) {
                    mark[nextRow][nextCol] = 1;
                    position.row = currentRow; position.col = currentCol;
                    position.dir = ++currentDir; //Why ?
                    mazeStackPush(position);
                    currentRow = nextRow; currentCol = nextCol; currentDir = 0;
                }
                else {
                    ++currentDir;
                }
            }
            else {
                ++currentDir;
            }
        }
    }

    if (found) {
        printf("The path is : \n");
        for (i = 0; i <= maze_top; i++) {
            printf("(%d,%d),", mazeStack[i].row, mazeStack[i].col);
        }
        printf("(%d,%d),",currentRow, currentCol);
        printf("(%d,%d)\n",end_x, end_y);
    }
    else {
        printf("No path!\n");
    }
}

void maze_function_driver() {

    init_move_array();
    
    maze = read_2d_array_from_file(file_name, &rows, &cols); 
    mark = get_2d_array(rows, cols);
    printMaze(maze, rows, cols);

    start_x = 0;
    start_y = 0;
    end_x = rows - 1; 
    end_y = cols - 1;

    MALLOC(mazeStack, rows * cols * sizeof(mazeElement));

    find_path();

    if (maze) {free2Darray(maze, rows, cols);}
    if (mark) {free2Darray(mark, rows, cols);}
    if (mazeStack) {free(mazeStack);}

}








/* Functions */


void printMazeStack() {
    int i = 0;
    printf("\nStack (from top) :\n");
    for (i = maze_top; i >= 0 ; i--) {
        printf("(%d, %d, %d)\n", mazeStack[i].row, mazeStack[i].col, mazeStack[i].dir);
    }
    printf("\n");
}

void mazeStackFull() {
    fprintf(stderr, "\nStack is full, cannot add element\n");
    printMazeStack();
    exit(EXIT_FAILURE);
}

mazeElement mazeStackEmpty() {
    printf("\nStack is empty, cannot remove element");
    mazeElement item;
    item.row = -1;
    item.col = -1;
    item.dir = -1;
    return item;
}

void mazeStackPush(mazeElement item) {
    if (maze_top >= rows*cols - 1)
        mazeStackFull();
    mazeStack[++maze_top] = item;
}

mazeElement mazeStackPop() {
    if (maze_top == -1)
        return mazeStackEmpty();
    return mazeStack[maze_top--];
}

int is_valid_pos(int x, int y) {
    if (x < 0 || x >= rows || y < 0 || y >= cols)
        return FALSE;
    else if (maze[x][y] == 1)
        return FALSE;
    return TRUE;
}

void printMaze(int** maze, int rows, int cols) {
    int i = 0, j = 0;
    //printf("rows : %d, cols : %d\n", rows, cols);
    printf(("x/y    | "));
    for (int i = 0; i < cols; i++) {
        printf("%4d ", i);
    }
    printf("\n    ");
    for (int i = 0; i < cols; i++) {
        printf("%4c ", '-');
    }
    printf("\n");
    for (i = 0; i < rows; i++) {
        printf("%3d    | ",i);
        for (j = 0; j < cols; j++) {
            printf("%4d ", *(*(maze + i) + j)); // or printf("%4d ", array[i][j]);
        }
        printf("\n");
    }
}

void init_move_array() {
    offset N; N.vert = -1; N.horiz = 0; move[0] = N;
    offset NE; NE.vert = -1; NE.horiz = 1 ; move[1] = NE; 
    offset E; E.vert = 0; E.horiz = 1; move[2] = E; 
    offset SE; SE.vert = 1; SE.horiz = 1; move[3] = SE; 
    offset S; S.vert = 1; S.horiz = 0; move[4] = S; 
    offset SW; SW.vert = 1; SW.horiz = -1; move[5] = SW; 
    offset W; W.vert = 0; W.horiz = -1; move[6] = W;
    offset NW; NW.vert = -1; NW.horiz = -1; move[7] = NW;  
}

//The path is : 
//(0,0),(1,1),(0,2),(0,3),(0,4),(1,3),(2,4),(2,3),(3,2),(4,2),(5,1),(6,1),(7,0),(8,1),(9,2),(9,3),(8,4),(7,5),(7,6),(8,7),(9,7),(10,8),(10,9),(9,10),(9,11),(9,12),(8,13),(9,14),(10,14),(11,14)
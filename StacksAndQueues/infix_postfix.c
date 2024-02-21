#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "utils.h"

#define IP_STACK_MAX_SIZE 50

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0}; //nothing for operand as it won't enter stack
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0};
//char exprn[32] = "62/3-42*+";
char exprn[32] = "54*82/+3-";

int ipStack[IP_STACK_MAX_SIZE];
int ipTop = -1;
precedence tokenStack[IP_STACK_MAX_SIZE];
int tokenTop = -1;


void printIpStack();
void ipStackFull();
void ipStackPush(int val);
int ipStackEmpty();
int ipStackPop();

void printTokenStack();
void tokenStackFull();
void tokenStackPush(precedence val);
precedence tokenStackEmpty();
precedence tokenStackPop();

precedence getToken(char* symbol, int* n) {
    *symbol = exprn[(*n)++];
    switch(*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '*': return times;
        case '/': return divide;
        case '%': return mod;
        case '\0': return eos;
        default: return operand;
    }
}

void printToken(precedence token) {
    switch(token) {
        case lparen: printf("("); break;
        case rparen: printf(")"); break;
        case plus: printf("+"); break;
        case minus: printf("-"); break;
        case times: printf("*"); break;
        case divide: printf("/"); break;
        case mod: printf("%%"); break;
        case eos: printf("%c",'\0'); break;
        default: printf("\nShould not reach here....\n");exit(1);
    }
}

int postfix_eval() {
    precedence token = eos;
    char symbol = '\0';
    int n = 0, op1 = 0, op2 = 0;
    token = getToken(&symbol, &n);
    while (token != eos) {
        //printIpStack();
        if (token == operand) {
            ipStackPush(symbol-'0');
        }
        else {
            op2 = ipStackPop();
            op1 = ipStackPop();
            switch(token) {
                case plus: ipStackPush(op1+op2); break;
                case minus: ipStackPush(op1-op2); break;
                case times: ipStackPush(op1*op2); break;
                case divide: ipStackPush(op1/op2); break;
                case mod: ipStackPush(op1%op2); break;
                default: printf("\nShould not reach here....\n");exit(1);
            }
        }
        token = getToken(&symbol, &n);
    }
    return ipStackPop();
}

void infix_to_postfix() {
    char symbol = '\0';
    precedence token, temp;
    int n = 0;
    token = eos; tokenStackPush(token);
    // can use previosuly used similar while loop also!
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
        if (token == operand) {
            printf("%c",symbol);
        }
        else if (token == rparen) {
            while (tokenStack[tokenTop] != lparen) {
                temp = tokenStackPop(); printToken(temp);
            }
            tokenStackPop();
        }
        else {
            while (isp[tokenStack[tokenTop]] >= icp[token]) {
                temp = tokenStackPop(); printToken(temp);
            }
            tokenStackPush(token);
        }
    }
    while (tokenStack[tokenTop] != eos) {
        temp = tokenStackPop();
        printToken(temp);
    }
    printf("\n");
}

void postfix_eval_driver() {
    int result = postfix_eval();
    printf("Result of expression %s is : %d\n",exprn, result);
    //sprintf(exprn,"a*(b+c)*d");
    //sprintf(exprn,"a+b*c");
    sprintf(exprn, "(a+b)*d+e/(f+g*h)+c");
    infix_to_postfix();

}











/*Stack functions*/
void printIpStack() {
    int i = 0;
    printf("\nPrinting stack from the top\n");
    for (i = ipTop; i >= 0 ; i--) {
        printf("%d ", ipStack[i]);
    }
    printf("\n");
}

void ipStackFull() {
    fprintf(stderr, "\nStack is full, cannot add element\n");
    printIpStack();
    exit(EXIT_FAILURE);
}

void ipStackPush(int val) {
    if (ipTop >= IP_STACK_MAX_SIZE - 1)
        ipStackFull();
    ipStack[++ipTop] = val;
}

int ipStackEmpty() {
    printf("\nStack is empty, cannot remove element");
    return -1;
}

int ipStackPop() {
    if (ipTop == -1)
        return ipStackEmpty();
    return ipStack[ipTop--];
}


/*token Stack functions*/
void printTokenStack() {
    int i = 0;
    printf("\nPrinting stack from the top\n");
    for (i = tokenTop; i >= 0 ; i--) {
        printf("%d ", tokenStack[i]);
    }
    printf("\n");
}

void tokenStackFull() {
    fprintf(stderr, "\nStack is full, cannot add element\n");
    printTokenStack();
    exit(EXIT_FAILURE);
}

void tokenStackPush(precedence val) {
    if (tokenTop >= IP_STACK_MAX_SIZE - 1)
        tokenStackFull();
    tokenStack[++tokenTop] = val;
}

precedence tokenStackEmpty() {
    printf("\nStack is empty, cannot remove element");
    return eos;
}

precedence tokenStackPop() {
    if (tokenTop == -1)
        return tokenStackEmpty();
    return tokenStack[tokenTop--];
}
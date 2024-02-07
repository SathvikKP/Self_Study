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
//char exprn[32] = "62/3-42*+";
char exprn[32] = "54*82/+3-";
int ipStack[IP_STACK_MAX_SIZE];
int ipTop = -1;

void printIpStack();
void ipStackFull();
void ipStackPush(int val);
int ipStackEmpty();
int ipStackPop();

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


void postfix_eval_driver() {
    int result = postfix_eval();
    printf("Result of expression %s is : %d\n",exprn, result);
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
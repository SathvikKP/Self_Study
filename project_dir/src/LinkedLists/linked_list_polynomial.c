#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../utils/utils.h"
#include "linked_list.h"

void ll_print_polynomial(polyPointer polynomial) {

    nl();

    polyPointer current = polynomial;
    printf("%dx^%d ", current->coef, current->expon);
    current = current->link;
    while (current) {
        if (current->coef >= 0 ) {
            printf("+ %dx^%d ", current->coef, current->expon);
        } else {
            printf("- %dx^%d ", (-1 * (current->coef)), current->expon);
        }
        current = current->link;
    }
    nl();
}

polyPointer ll_create_polynomial_node(int coef, int expon) {
    polyPointer node = NULL;
    MALLOC(node, sizeof(polyNode));
    node->coef = coef;
    node->expon = expon;
    node->link = NULL;
    return node;
}

/*Assumes expon_array is in decreasing order*/
polyPointer ll_create_polynomial(int coef_array[], int expon_array[], int array_size) {
    
    polyPointer polynomial = NULL;
    polyPointer current = NULL;
    polyPointer node = NULL;
    int i = 0, coef = 0, expon = 0;

    for (i = 0; i < array_size; i++) {
        coef = coef_array[i]; expon = expon_array[i];
        //printf("%d %d\n", coef, expon);
        node = ll_create_polynomial_node(coef, expon);
        if (i == 0) {
            polynomial = node;
            polynomial->link = NULL;
        } else {
            current->link = node;
        }
        current = node; node = NULL;
    }
    printf("\nPolynomial Created!\n");
    //ll_print_polynomial(polynomial);
    return polynomial;
}

void ll_free_polynomial(polyPointer *polynomial) {
    polyPointer current = *polynomial;
    polyPointer next = NULL;
    while (current) {
        next = current->link;
        free(current);
        current = next;
    }
    *polynomial = NULL;
    printf("\nPolynomial freed!\n");
}

polyPointer ll_add_polynomial(polyPointer polyA, polyPointer polyB) {
    if (!polyA && !polyB) return NULL;

    polyPointer polyC = NULL;
    polyPointer node = NULL;
    polyPointer tempFirstNode = ll_create_polynomial_node(-1, -1);
    tempFirstNode->link = NULL;
    polyC = tempFirstNode;

    while (polyA && polyB) {
        switch (COMPARE(polyA->expon, polyB->expon)) {
            case 0:
                if (((polyA->coef) + (polyB->coef)) != 0) {
                    node = ll_create_polynomial_node(((polyA->coef) + (polyB->coef)), polyA->expon);
                    polyC->link = node; polyC = node;
                }
                polyA = polyA->link; polyB = polyB->link;
                break;
            case 1:
                node = ll_create_polynomial_node(polyA->coef, polyA->expon);
                polyC->link = node; polyC = node;
                polyA = polyA->link;
                break;
            case -1:
                node = ll_create_polynomial_node(polyB->coef, polyB->expon);
                polyC->link = node; polyC = node;
                polyB = polyB->link;
                break;
            default:
                printf("\n\nERROR!\n\n"); break;
        }
    }
    while (polyA) {
        node = ll_create_polynomial_node(polyA->coef, polyA->expon);
        polyC->link = node; polyC = node;
        polyA = polyA->link;
    }
    while (polyB) {
        node = ll_create_polynomial_node(polyB->coef, polyB->expon);
        polyC->link = node; polyC = node;
        polyB = polyB->link;
    }

    //polyC->link = NULL;
    //remove the first temporary node!
    polyC = tempFirstNode->link;
    if (tempFirstNode) free(tempFirstNode);

    printf("\nPolynomial Added!\n");
    return polyC;
}

void linked_list_polynomial_driver() {
/*
    int poly1NumTerms = 3;
    int poly1Coef[3] = {3, 5, -3};
    int poly1Expon[3] = {2, 1, 0};

    int poly2NumTerms = 3;
    int poly2Coef[3] = {1, -5, 3};
    int poly2Expon[3] = {2, 1, 0}; 
*/
/*
    int poly1NumTerms = 4;
    int poly1Coef[4] = {1, 3, -1, -8};
    int poly1Expon[4] = {5, 3, 1, 0};
    int poly2NumTerms = 4;
    int poly2Coef[4] = {2, -5, 3, 12};
    int poly2Expon[4] = {4, 3, 2, 0}; 
*/
    
    int poly1NumTerms = 3;
    int poly1Coef[3] = {3, 2, 1};
    int poly1Expon[3] = {14, 8, 0};

    int poly2NumTerms = 3;
    int poly2Coef[3] = {8, -3, 10};
    int poly2Expon[3] = {14, 10, 6}; 
    
    
    polyPointer polyA = ll_create_polynomial(poly1Coef, poly1Expon, poly1NumTerms);
    polyPointer polyB = ll_create_polynomial(poly2Coef, poly2Expon, poly2NumTerms);
    polyPointer polyC = ll_add_polynomial(polyA, polyB);

    ll_print_polynomial(polyA); ll_print_polynomial(polyB); ll_print_polynomial(polyC);

    ll_free_polynomial(&polyA); ll_free_polynomial(&polyB); ll_free_polynomial(&polyC);

    //ll_print_polynomial(polyA);
    
}
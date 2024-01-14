#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "utils.h"


#define MAX_TERMS 100

typedef struct {
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;


void print_terms_array() {
    int i = 0;
    for (i = 0; i < avail; i++) {
        printf("%4.0f ",terms[i].coef);
    }
    printf("\n");
    for (i = 0; i < avail; i++) {
        printf("%4d ",terms[i].expon);
    }
    printf("\n");
}

void initialize_global_polynomial_array(float A_c[], int A_e[], int size_a, float B_c[], int B_e[], int size_b,
int* start_a, int* finish_a, int* start_b, int* finish_b) {
    int i = 0;
    *start_a = avail;
    for (i = 0; i < size_a; i++) {
        terms[avail].coef = A_c[i];
        terms[avail].expon = A_e[i];
        avail++;
    }
    *finish_a = avail - 1;
    *start_b = avail;
    for (i = 0; i < size_b; i++) {
        terms[avail].coef = B_c[i];
        terms[avail].expon = B_e[i];
        avail++;
    }
    *finish_b = avail-1;
}

void attach(float coef, int expon) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "LIMIT EXCEEDED!\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
    float coef = 0;
    *startD = avail;
    while (startA <= finishA && startB <= finishB) {
        switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
            case -1:
                attach(terms[startB].coef, terms[startB].expon);
                startB++;
                break;
            case 0 :
                coef = terms[startA].coef + terms[startB].coef;
                if (coef) {
                    attach(coef, terms[startA].expon);
                }
                startA++; startB++;
                break;
            case 1 :
                attach(terms[startA].coef, terms[startA].expon);
                startA++;
                break;
        }
    }
    for (; startA <= finishA; startA ++) {
        attach(terms[startA].coef, terms[startA].expon);
    }
    for (; startB <= finishB; startB ++) {
        attach(terms[startB].coef, terms[startB].expon);
    }
    *finishD = avail - 1;
}

void polynomial_add_array_driver() {

    int size_a = 2;
    int size_b = 4;

    float A_c[2] = {2 , 1};
    int A_e[2] = {3, 0};
    float B_c[4] = {1,10, 3, 1};
    int B_e[4] = {4, 3, 2, 0};

    int start_a = 0, finish_a = 0, start_b = 0, finish_b = 0, start_d = 0, finish_d = 0;

    initialize_global_polynomial_array(A_c, A_e, size_a, B_c, B_e, size_b, &start_a, &finish_a, &start_b, &finish_b);
    print_terms_array();
    padd(start_a, finish_a, start_b, finish_b, &start_d, &finish_d);
    print_terms_array();


}
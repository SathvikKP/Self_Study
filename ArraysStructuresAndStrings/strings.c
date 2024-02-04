#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "utils.h"

#define MAX_SIZE 128

void strnins(char* s, char* t, int i) {
    char string[MAX_SIZE];
    char* temp = string;
    if (i < 0 || i > strlen(s)) {
        fprintf(stderr, "out of bounds");
        exit(EXIT_FAILURE);
    }
    if (!strlen(s)) {
        strcpy(s, t);
    }
    else if (strlen(t)) {
        strncpy(temp, s, i);
        temp[i] = '\0';
        strcat(temp, t);
        strcat(temp, (s+i));
        strcpy(s, temp);
    }
}

int patten_match_end_indices(char* str, char* pat) {
    int i = 0, j = 0, start = 0, endmatch = 0, lasts = 0, lastp = 0;
    lastp = strlen(pat) - 1;
    lasts = strlen(str) - 1;
    start = 0; endmatch = lastp;

    for (i = 0; endmatch <= lasts; start++, endmatch++) {
        if (str[endmatch] == pat[lastp]) {
            for (i = start, j = 0; j < lastp && str[i] == pat[j]; i++, j++);
            if (j == lastp) {
                return start;
            }
        } 
    }
    return -1;
}

//failure(j) assumes string length > 2
int* failure_function(char* pattern) {
    int n = strlen(pattern);
    int i = 0, j = 0;
    int* failure = get_array(n);
    failure[0] = -1;

    for (j = 1; j < n; j++) {
        i = failure[j-1];
        while ((pattern[j] != pattern[i+1]) && (i >= 0)) {
            i = failure[i];
        }
        if (pattern[j] == pattern[i+1]) {
            failure[j] = i + 1;
        }
        else {
            failure[j] = -1;
        }
    }
    printarray(failure, n);
    return failure;
}

int KMP_Algorithm(char* str, char* pat) {
    int i = 0, j = 0;
    int str_len = strlen(str);
    int pat_len = strlen(pat);
    int* failure = failure_function(pat);

    while (i < str_len && j < pat_len) {
        if (str[i] == pat[j]) {
            i++; j++;
        }
        else if (j == 0) {
            i++;
        }
        else {
            j = failure[j-1] + 1;
        }
    }
    if (failure) {free(failure);}
    return ( (j == pat_len) ? (i - pat_len) : -1);
}

void strings_driver() {
    char string1[MAX_SIZE] = "Amobile";
    char string2[MAX_SIZE] = "uto";
    char* s = string1;
    char* t = string2;
    puts(s);
    puts(t);
    //strnins(s, t, 1);
    puts(s);

    char str[MAX_SIZE] = "ababbaabaa";
    char pat[MAX_SIZE] = "aab";
    printf("Searching for \"%s\" in \"%s\" | Result : %d\n", pat, str, patten_match_end_indices(str, pat));

    //printf("Searching for \"%s\" in \"%s\" | Result : %d\n", pat, str, KMP_Algorithm(str, pat));

    strcpy(str, "This is a sample search string");
    strcpy(pat, "sample");
    printf("Searching for \"%s\" in \"%s\" | Result : %d\n", pat, str, patten_match_end_indices(str, pat));

    char* pattern = "abcabcacab";
    int* failure_array = failure_function(pattern);
    if (failure_array){free(failure_array);}

    strcpy(str, "abaaabbaaabaabbbaaabbaaabbaabbaaa");
    strcpy(pat, "aabbaabb");
    
    printf("Searching for \"%s\" in \"%s\" | Result : %d\n", pat, str, KMP_Algorithm(str, pat));
    


}
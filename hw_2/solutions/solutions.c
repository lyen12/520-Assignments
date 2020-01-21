#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solutions.h"

#define INITIAL_STACK_SIZE 100

static int total = 0;

int running_total (int a) {
    return total += a; //total = total + a
}

//Function to print array solution for testing purposes
void print_array (int a[], int b) {
    for ( int i = 0; i < b; i++) {
        printf( "%d ", a[i]);
    }
    printf("\n");
}

void reverse_in_place (int a[], int b) {
    int hold;   //holds original a[i] value for swapping
    int element = b-1;  //Starting point for last element

    for ( int i = 0; i < element; i++, element-- ) {
        hold = a[i];
        a[i] = a[element];
        a[element] = hold;
        print_array (a, b);
    }
}

int reverse (int a);

int num_instances (int a);

Point map( Point a);




  

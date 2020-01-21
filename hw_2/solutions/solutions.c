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

void reverse_in_place (int a[], int length_of_a) {
    int hold;   //holds original a[i] value for swapping
    int element = length_of_a-1;  //Starting point for last element

    //swap the elements to place in reverse
    for ( int i = 0; i < element; i++, element-- ) {
        hold = a[i];
        a[i] = a[element];
        a[element] = hold;
        print_array (a, length_of_a);
    }
}

int *reverse (int a[], int length_of_a) {
    int *new_array = (int *)calloc( length_of_a, sizeof(int) );    

    //Place elements of input array into new array in reverse order
    for (int i = 0; i < length_of_a; i++) {
        new_array[i] = a[ ( length_of_a-1 ) - i ];
    }
    print_array( new_array, length_of_a);
    return new_array;
}

//This function uses a recursive function to count through each element of the array
int num_instances (int a[], int length_of_a, int value) {
     if ( length_of_a <= 0 ) { return 0; }
     if ( a[0] == value ) { 
        return 1 + num_instances (a+1, length_of_a-1, value);  
    }
    else {
        return num_instances (a+1, length_of_a-1, value);
    }
}

Point *map( Point a[], int length_of_a, Point (*fn_ptr)(Point)) {
    Point *solution = (Point *)malloc(length_of_a*sizeof(Point));
    for ( ; length_of_a > 0; length_of_a-- ) {
        solution[length_of_a - 1] = (*fn_ptr)(a[length_of_a - 1]);
    }
    return solution;
}





  

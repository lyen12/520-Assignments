#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>

/*Running_total keeps track of track of the sum of 
the arguments it has been called with over time*/
int running_total (int a);

/*Reverse_in_place takes an array and its length and 
reverses it in place. Something like the following tests should pass*/
void reverse_in_place (int a[], int b);

/*Reverse takes an array and its length and returns a new 
array that is the reverse of the given array*/ 
int reverse (int a);

/*Num_instances takes an array of integers, a length, and a value and 
returns the number of instances of that value in the array*/
int num_instances (int a);

/*A point object at x, y, z coordinates*/
typedef struct {
   double x, y, z;
 } Point;

/*Map takes an array of Points, its length, and a function pointer that 
returns a newly allocated array whose values are the values of the function 
argument applied to the array argument.*/
Point map( Point a);

#endif
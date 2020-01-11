#include <stdio.h>
#include <math.h>
#include "complex.h"

Complex add ( Complex a, Complex b ) {
    return (Complex) { a.real + b.real, a.im + b.im };
}

Complex negate ( Complex a ) {
    return (Complex) { -1*a.real, -1*a.im};
}

Complex multiply ( Complex a, Complex b ) {
    return (Complex) { (a.real*b.real) + (-1*(a.im*b.im)) , (a.real*b.im) + (a.im*b.real) };
}

double magnitude ( Complex a ) {
    double z_mag = sqrt( pow(a.real, 2) + pow(a.im, 2) );
    return z_mag;
}
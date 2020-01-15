#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

/*GCD Function to determine the greatest common denominator*/
/*This function uses the Euclidean Algorithm to determine the GCD*/
int GCD ( int a, int b ) {
  int divisor, dividend;
  a = abs(a);
  b = abs(b);
  //Find which is the greater integer (num or den) and set the smaller integer as the divisor
  if ( a < b ) {
      divisor = a;
      dividend = b; 
  }
  else {
      divisor = b;
      dividend = a;
  }
  //Euclidian Algorithm 
  int remainder = divisor;
  int greatest_common_denominator;
  while ( remainder != 0 ) {
      greatest_common_denominator = remainder;
      remainder = dividend % divisor;
      dividend = divisor;
      divisor = remainder;
      }
  return greatest_common_denominator;
}

//Reduce fraction to convert fraction to simplest form
Fraction reduce ( Fraction a ) {
    if ( a.num == 0 && a.den == 0 ) return a;
    if (a. num == 0 && a.den != 0) return (Fraction) {0, 1};
    if (a. num != 0 && a.den == 0) return (Fraction) {1, 0}; 

    int numerator = a.num;
    int denominator = a.den;
    if (a.den < 0 && a.num > 0) {
        numerator = -a.num;
        denominator = -a.den;
    }
    if (a.num < 0 && a.den < 0) {
        numerator = abs(a.num);
        denominator = abs(a.den);
    }

    int greatest_common_denominator = GCD ( a.num, a.den );
    return (Fraction) {numerator / greatest_common_denominator, denominator / greatest_common_denominator};
}
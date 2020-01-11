#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

/*Print answer of Fraction for testing*/
void printanswer ( Fraction answer ) {
  printf("%d / %d \n", answer.num, answer.den);
}

/*GCD Function to determin the greatest common denominator*/
int GCD ( int a, int b ) {
  int divisor, dividend;
  a = abs(a);
  b = abs(b);
  if ( a < b ) {
      divisor = a;
      dividend = b; 
  }
  else {
      divisor = b;
      dividend = a;
  }
  int remainder = divisor;
  int greatest_common_denominator;
  while ( remainder != 0 ) {
      greatest_common_denominator = remainder;
      remainder = dividend % divisor;
      dividend = divisor;
      divisor = remainder;
      
      //printf("GCD is %d\n", greatest_common_denominator);
  }
  return greatest_common_denominator;
}

Fraction reduce ( Fraction a ) {
    if ( a.num == 0 || a.den == 0 ) return a;
    int greatest_common_denominator = GCD ( a.num, a.den );
    return (Fraction) {a.num / greatest_common_denominator, a.den / greatest_common_denominator};
}
#ifndef COMPLEX_H
#define COMPLEX_H

/*! \Brief Complex object and method definitions
 *
 *  A Complex object is a struct with a real number, denoted real, and
 *  an imaginary number, denoted im. Various Methods that take complex numbers and return 
 *  complex numbers do arithmetical operations on them. 
 */
typedef struct { 
    double real;    
    double im;
} Complex;

/*! Add two Complex numbers together
 *  \param a The first summand
 *  \param b The second summand
 *  i.e (x + yi) + (w + zi) -> ((x + w) + (y + z)i)
 */
Complex add ( Complex a, Complex b );

/*! Negate a Complex Number 
 *  \param a The first term
 *  i.e. (x + yi) -> (-x - yi)
 */
Complex negate ( Complex a );

/*! Multiply two Complex numbers together
 *  \param a The first term
 *  \param b The second term
 *  i.e (x + yi)*(w + zi) -> ((x*w) + (x*zi) + (yi*w) + (yi*zi)), replace i^2 with (-1)
 */
Complex multiply ( Complex a, Complex b );

/*! Find Magnitude of two Complex numbers together
 *  \param a The first term
 *  i.e. |(x + yi)| -> sqrt(x^2 + y^2)
 */
double magnitude ( Complex a );

/*! Prints the resulting answer*/
void printcomplexanswer ( Complex a );

/*! Prints the resulting answer*/
void printanswer ( double a );

#endif
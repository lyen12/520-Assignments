#include <math.h>
#include "complex.h"

double Complex::magnitude() const {
    return sqrt(re*re + im*im);
}

bool operator<(const Complex& a, const Complex& b) {
    return a.magnitude() < b.magnitude();
}

double Complex::real() const {
	return re;
}

double Complex::imaginary() const {
	return im;
}

Complex Complex::conjugate() const {
	Complex conj = Complex( re, -im );
	return conj;
}

Complex Complex::operator*( const Complex &other ) {
	Complex mult = Complex (this->re*other.re, this->im*other.im);
	return mult;
}

Complex Complex::operator+( const Complex &other ) {
	Complex add = Complex (this->re + other.re, this->im + other.im);
	return add;
}

bool Complex::operator==( const Complex &other ) {
	if (this->re == other.re && this->im == other.im) {
		return true;
	} else { return false; }

}
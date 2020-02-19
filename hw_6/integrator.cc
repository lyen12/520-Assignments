#include <stdlib.h>
#include <iostream>
#include <ratio>
#include "integrator.h"
#include "elma/elma.h"


using namespace elma;
using namespace std;

Integrator::Integrator(string name) : Process(name) {}

void Integrator::init() {
	integral = 0;
}
void Integrator::start() {}
void Integrator::stop() {}

void Integrator::update() {	
	v = channel("link").latest();
	integral += (delta() * v);
	cout << "v is " << v << "\n";
	cout << "Delta is " << delta() << "\n";
	cout << "The integral is " << integral << "\n";

}

double Integrator::value() {
	//cout << "The integral is " << integral << "\n";
	return integral;
}
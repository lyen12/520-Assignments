#include <stdlib.h>
#include <iostream>
#include <ratio>
#include "derivative.h"
#include "elma/elma.h"


using namespace elma;
using namespace std;

Derivative::Derivative(string name) : Process(name) {}

void Derivative::init() {
	derivative = 0;
}
void Derivative::start() {
	current_v = 0;
	previous_v = 0;
}
void Derivative::stop() {}

void Derivative::update() {	
	current_v = channel("link").latest();
	cout << "current v is " << current_v << "\n";
	cout << "previous v is " << previous_v << "\n";
	derivative  = (current_v - previous_v) / delta();
	previous_v = current_v;

	cout << "Delta is " << delta() << "\n";
	cout << "The derivative is " << derivative << "\n";

}

double Derivative::value() {
	cout << "The final derivative is " << derivative << "\n";
	return derivative;
}
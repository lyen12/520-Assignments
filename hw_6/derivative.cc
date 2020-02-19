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
	two_runs = 0;
}
void Derivative::stop() {}

void Derivative::update() {
	current_v = channel("link").latest();
	cout << "current v is " << current_v << "\n";
	derivative  = (current_v - previous_v) / delta();
	cout << "previous v is " << previous_v << "\n";
	previous_v = current_v;
	cout << "Delta is " << delta() << "\n";
	//cout << "The derivative is " << derivative << "\n";
	two_runs++;
}

double Derivative::value() {
	if (two_runs < 2) {
		cout << "Process has not read in two values\n"; 
		return 0; 
	}
	cout << "The final derivative is " << derivative << "\n";
	return derivative;
}
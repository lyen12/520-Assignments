#include "elma/elma.h"
#include <stdlib.h>
#include <iostream>
#include <ratio>

using namespace elma;
using namespace std;

class Derivative : public Process {
	public:
		Derivative(string name);
		void init();
		void start();
		void stop();
		void update();
		double value();

	private:
		double derivative;
		double previous_v;
		double current_v;

};
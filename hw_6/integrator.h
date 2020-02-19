#include "elma/elma.h"
#include <stdlib.h>
#include <iostream>
#include <ratio>

using namespace elma;
using namespace std;

class Integrator : public Process {
	public:
		Integrator(string name);
		void init();
		void start();
		void stop();
		void update();
		double value();

	private:
		double integral;
		double v;

};
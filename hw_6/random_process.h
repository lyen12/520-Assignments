#include "elma/elma.h"
#include <stdlib.h>
#include <iostream>
#include <ratio>

using namespace elma;
using namespace std;

class RandomProcess : public Process {
	public:
		RandomProcess(string name);
		void init();
		void start();
		void stop();
		void update();

	private:
		double random_double;
		double randZeroToOne();


};
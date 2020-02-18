#include "elma/elma.h"
#include <stdlib.h>
#include <iostream>
#include <ratio>

using namespace elma;
using namespace std;

class TestProcess : public Process {

	public:
		TestProcess(string name);
		void init();
		void start();
		void stop();
		void update();

	private:
		int counter;
};
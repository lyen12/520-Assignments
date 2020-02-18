#include "elma/elma.h"
#include <stdlib.h>
#include <iostream>

using namespace elma;
using namespace std;

class Filter : public Process {
	public:
		Filter(string name);		
		void init();
		void start();
		void stop();
		void update();
		double value();

	private:
		vector<double> last_ten_link_numbers;
		double average;

};
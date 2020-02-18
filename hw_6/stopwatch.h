#include <iostream>
#include <ratio>
#include <chrono>
#include <ctime>
#include "elma/elma.h"

using namespace elma;
using namespace std::chrono;

class Stopwatch : public Process {

    public:
    	Stopwatch();
    	void init();
    	void update();
		void start();
		void stop();
		void reset();

		double get_minutes();      // number of minutes counted, as a double
		double get_seconds();      // number of seconds counted, as a double
		double get_milliseconds(); // number of milliseconds counted, as a double
		double get_nanoseconds();  // number of nanoseconds counted, as a double


	private:
		high_resolution_clock::time_point t_start, t_stop;
		duration<double> time_elapsed;
		typedef duration<double,std::ratio<1,1000>> milliseconds;
		typedef duration<double,std::ratio<1,1>> seconds;
		typedef duration<double,std::ratio<60,1>> minutes;

};
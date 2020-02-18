#include <iostream>
#include <ratio>
#include <chrono>
#include <ctime>
#include "stopwatch.h"
#include "elma/elma.h"


using namespace elma;
using namespace std::chrono;
using namespace std;

Stopwatch::Stopwatch() : Process() {}

void Stopwatch::init() {
	time_elapsed = high_resolution_clock::duration::zero();
}

void Stopwatch::update() {}

void Stopwatch::start() {
	t_start = high_resolution_clock::now();

}

void Stopwatch::stop() {
	t_stop = high_resolution_clock::now();
	time_elapsed = time_elapsed + (t_stop - t_start);
	cout << "Time elapsed is " << (t_stop - t_start).count() << " seconds\n";

}

void Stopwatch::reset() {
	time_elapsed = high_resolution_clock::duration::zero();
}

double Stopwatch::get_minutes() {      // number of minutes counted, as a double
	return minutes(time_elapsed).count();
}
double Stopwatch::get_seconds() {      // number of seconds counted, as a double
	return seconds(time_elapsed).count();

}
double Stopwatch::get_milliseconds() { // number of milliseconds counted, as a double
	return milliseconds(time_elapsed).count();
}
double Stopwatch::get_nanoseconds() {  // number of nanoseconds counted, as a double
	return time_elapsed.count();
}






#include <stdlib.h>
#include <iostream>
#include <ratio>
#include "test_process.h"
#include "elma/elma.h"

using namespace elma;
using namespace std;

TestProcess::TestProcess(string name) : Process(name) {}

void TestProcess::init() {}
void TestProcess::start() {
	counter = 1;
}
void TestProcess::stop() {}

void TestProcess::update() {
	// if (counter % 2 == 0) {
 // 		channel("link").send(0.25);	
 // 		counter ++;
	// } else {
	// 	channel("link").send(0.75);	
	// 	counter++;
	// }

	channel("link").send(counter);
	counter++;

  
}

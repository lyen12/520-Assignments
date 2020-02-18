#include <stdlib.h>
#include <iostream>
#include <ratio>
#include "random_process.h"
#include "elma/elma.h"

using namespace elma;
using namespace std;

RandomProcess::RandomProcess(string name) : Process(name) {}

void RandomProcess::init() {}
void RandomProcess::start() {}
void RandomProcess::stop() {}

double RandomProcess::randZeroToOne() {
    return rand() / (RAND_MAX + 1.0);
}

void RandomProcess::update() {
  channel("link").send(randZeroToOne());
}




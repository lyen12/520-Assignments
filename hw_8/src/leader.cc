#include <iostream>
#include <cstdlib>
#include "leader.h"

using namespace enviro;
using namespace std;


LeaderController::LeaderController() : Process(), AgentInterface() {}

void LeaderController::init() {}
void LeaderController::start() {}
void LeaderController::update() {
	track_velocity(10,1);
    emit(Event("cheese_change", { 
	    { "x", position().x }, 
	    { "y", position().y } 
	}));
}
void LeaderController::stop() {}
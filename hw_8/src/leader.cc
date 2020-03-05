#include <iostream>
#include <cstdlib>
#include "leader.h"

using namespace enviro;
using namespace std;


LeaderController::LeaderController() : Process(), AgentInterface() {}

void LeaderController::init() {}
void LeaderController::start() {}
void LeaderController::update() {
	
    emit(Event("cheese_change", { 
	    { "x", position().x }, 
	    { "y", position().y } 
	}));

    if ( sensor_value(0) < 50 ) {
    	track_velocity(0,7);
	} else {
		track_velocity(8,0.20);
	}
}
void LeaderController::stop() {}
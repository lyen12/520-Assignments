#include <iostream>
#include "follower.h"

using namespace enviro;
using namespace std;

FollowerController::FollowerController() : StateMachine(), AgentInterface() {}

void FollowerController::init() {}
void FollowerController::start() {}
void FollowerController::update() {
	/*The mouse will watch for the cheese_change event and move towards the cheese*/
	watch("cheese_change", [this](Event e) {
	    goal_x = e.value()["x"];
	    goal_y = e.value()["y"];
	});

	if ( sensor_value(0) < 30 ) {
    	track_velocity(0,0.2);
	} else {  
	move_toward(goal_x, goal_y);
	}



}
void FollowerController::stop() {}
#include <iostream>
#include "follower_2.h"

using namespace enviro;
using namespace std;

Follower_2Controller::Follower_2Controller() : StateMachine(), AgentInterface() {}

void Follower_2Controller::init() {}
void Follower_2Controller::start() {}
void Follower_2Controller::update() {
	/*The mouse will watch for the cheese_change event and move towards the cheese*/
	watch("mouse1_change", [this](Event e) {
	    goal_x = e.value()["mx"];
	    goal_y = e.value()["my"];
	});

	if ( sensor_value(0) < 30 ) {
    	track_velocity(0,0);
	} else {  
	move_toward(goal_x, goal_y);
	}



}
void Follower_2Controller::stop() {}
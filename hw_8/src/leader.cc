#include <iostream>
#include <cstdlib>
#include "leader.h"

using namespace enviro;
using namespace std;


MovingForward::MovingForward() : State(), AgentInterface() {}
void MovingForward::entry(const Event& e) {}
void MovingForward::during() {
  track_velocity(9,0); // Go forward
	if ( sensor_value(0) <= 70 ) {
	    emit(Event("wall"));
	}  
}
void MovingForward::exit(const Event& e) {}

Rotating::Rotating() : State(), AgentInterface() {}
void Rotating::entry(const Event& e) {
	init_angle = angle();
}
void Rotating::during() {
    track_velocity(0,2); // Rotate
    stop_angle = angle();
    diff_angle = stop_angle - init_angle;

    if ( fabs(diff_angle) > 3.14/4 ) {

        emit(Event("go"));
    }
}
void Rotating::exit(const Event& e) {}
LeaderController::LeaderController() : StateMachine(), AgentInterface() {
	set_initial(moving_forward);
	add_transition("wall", moving_forward, rotate);
    add_transition("go", rotate, moving_forward);
}

void LeaderController::update() {
    emit(Event("cheese_change", { 
	    { "x", position().x }, 
	    { "y", position().y } 
	}));
 
	StateMachine::update();
}
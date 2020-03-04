#include <iostream>
#include "follower.h"

using namespace enviro;
using namespace std;

FollowerController::FollowerController() : StateMachine(), AgentInterface() {
        // set_initial(following_cheese);
        // add_transition("lost", following_cheese, scan_left);
        // add_transition("found", scan_left, following_cheese);
        // add_transition("lost", scan_left, scan_right);
        // add_transition("found", scan_right, following_cheese);
}

void FollowerController::init() {

}
void FollowerController::start() {}
void FollowerController::update() {

watch("cheese_change", [this](Event e) {
    goal_x = e.value()["x"];
    goal_y = e.value()["y"];
});
move_toward(goal_x, goal_y);

}
void FollowerController::stop() {}
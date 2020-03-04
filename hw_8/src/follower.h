#ifndef __FOLLOWER_AGENT__H
#define __FOLLOWER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class FollowerController : public StateMachine, public AgentInterface {

    public:
    FollowerController();

    void init();
    void start();
    void update();
    void stop();

    private:
    double goal_x, goal_y;
    // FollowingCheese following_cheese;
    // ScanCheeseLeft scan_left;
    // ScanCheeseRight scan_right;
};

class Follower : public Agent {
    public:
    Follower(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FollowerController c;
};

//Create a State that will follow the Cheese
// class FollowingCheese : public State, public AgentInterface {
//     public:
//     FollowingCheese(std::string name) : State(name) {}
//     void entry(const Event& e) {}
//     void during() {
//         track_velocity(0,1);
//         if ( sensor_value(0) > 40 ) {
//             emit(Event("lost"));
//         } 
//     }
//     void exit(const Event&) {}
// };

// //Create a State that will look for the Cheese
// class ScanCheeseLeft : public State, public AgentInterface {
//     public:
//     ScanCheeseLeft(std::string name) : State(name) {}
//     void entry(const Event& e) {}
//     void during() {
//         track_velocity(0,1);
//         if ( sensor_value(0) > 40 ) {
//             emit(Event("lost"));
//         }     
//     }
//     void exit(const Event&) {}
// };

// //Create a State that will look for the Cheese
// class ScanCheeseRight : public State, public AgentInterface {
//     public:
//     ScanCheeseRight(std::string name) : State(name) {}
//     void entry(const Event& e) {}
//     void during() {}
//     void exit(const Event&) {}
// };

DECLARE_INTERFACE(Follower)

#endif
#ifndef __FOLLOWER_2_AGENT__H
#define __FOLLOWER_2_AGENT__H 

#include "enviro.h"

using namespace enviro;

class Follower_2Controller : public StateMachine, public AgentInterface {

    public:
    Follower_2Controller();

    void init();
    void start();
    void update();
    void stop();

    private:
    double goal_x, goal_y;

};

class Follower_2 : public Agent {
    public:
    Follower_2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    Follower_2Controller c;
};

DECLARE_INTERFACE(Follower_2)

#endif
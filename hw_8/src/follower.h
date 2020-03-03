#ifndef __FOLLOWER_AGENT__H
#define __FOLLOWER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class FollowerController : public Process, public AgentInterface {

    public:
    FollowerController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class Follower : public Agent {
    public:
    Follower(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FollowerController c;
};

DECLARE_INTERFACE(Follower)

#endif
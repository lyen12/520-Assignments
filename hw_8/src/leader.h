#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class LeaderController : public Process, public AgentInterface {

    public:
    LeaderController();
    void init();
    void start();
    void update();
    void stop();

};

class Leader : public Agent {
    public:
    Leader(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    LeaderController c;
};

DECLARE_INTERFACE(Leader)

#endif
#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class Rotating : public State, public AgentInterface {
    public:
    Rotating();
    void entry(const Event& e);
    void during();
    void exit(const Event& e);   

    private:
    double init_angle;
    double stop_angle;
    double diff_angle;
};

class MovingForward : public State, public AgentInterface {
    public:
    MovingForward();
    void entry(const Event& e);
    void during();
    void exit(const Event& e);
    
};

class LeaderController : public StateMachine, public AgentInterface {

    public:
    LeaderController();
    void update();

    private:
    MovingForward moving_forward;
    Rotating rotate;  

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
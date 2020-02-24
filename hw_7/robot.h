#ifndef _ROBOT_H
#define _ROBOT_H

#include "elma/elma.h"
#include <stdlib.h>
#include <iostream>
#include <set>
#include <json/json.h>

using nlohmann::json;

using namespace elma;
using namespace std;

class Mode : public State {
    public:
    Mode(std::string name) : State(name) {}
    void entry(const Event& e) {
        cout << "entering " + name() << "\n";
    }
    void during() {}
    void exit(const Event&) {}
};

class BetterStateMachine : public StateMachine {

    public:

    	BetterStateMachine(string name) : StateMachine(name) {}

   		json to_json() const {
   			json statemach_json;
   			set<string> state_set;
   			state_set.insert(_initial->name());
   			for ( auto t : _transitions) {
   				json trans_json;
   				trans_json["from"] = t.from().name();
   				trans_json["to"] = t.to().name();
   				trans_json["when"] = t.event_name();
   				statemach_json["transitions"].push_back(trans_json);

   				//Capture all the unique states
   				state_set.insert(t.from().name());
   				state_set.insert(t.to().name());
   			}

   			statemach_json["name"] = const_cast<BetterStateMachine*>(this)->name();
   			statemach_json["states"] = json (state_set);

   			return statemach_json;

		};

};
class Robot : public BetterStateMachine {

    public:

    Robot(string name) : BetterStateMachine(name) {

        set_initial(wander);
        add_transition("battery low", wander, find_recharge_station);
        add_transition("intruder detected", wander, make_noise);
        add_transition("found recharge station", find_recharge_station, recharge);
        add_transition("battery full", recharge, wander);
        add_transition("reset", make_noise, wander);
        add_transition("proximity warning", make_noise, evade);
        add_transition("reset", evade, make_noise);
        add_transition("battery low", evade, find_recharge_station);

    }

    private:
		Mode wander = Mode("Wander");
		Mode make_noise = Mode("Make Noise"); 
		Mode evade = Mode("Evade");
		Mode find_recharge_station = Mode("Find Recharge Station");
		Mode recharge = Mode("Recharge");

};


#endif
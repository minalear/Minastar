//
// Created by Trevor Fisher on 2/25/2018.
//

#ifndef SINISTAR_SOLDIER_CONTROLLER_H
#define SINISTAR_SOLDIER_CONTROLLER_H

#include "ship_controller.h"

enum struct SOLDIER_STATES {
    Patrol, //Roams randomly
    Defend, //Will swarm Sinistar when he is low health
    Attack, //Seek/Destroy player character
};

class soldier_controller: public ship_controller {
private:
    SOLDIER_STATES current_state;
    glm::vec2 wander_target;
    class game_entity *help_target;

public:
    soldier_controller();
    void update(float dt) override;
    void on_message(MESSAGE_TYPES &message, game_entity &other) override;
};


#endif //SINISTAR_SOLDIER_CONTROLLER_H

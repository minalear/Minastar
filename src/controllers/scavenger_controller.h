//
// Created by Trevor Fisher on 3/3/2018.
//

#ifndef SINISTAR_SCAVENGER_CONTROLLER_H
#define SINISTAR_SCAVENGER_CONTROLLER_H

#include "ship_controller.h"

enum struct SCAVENGER_STATES {
    Wander,
    Steal,
};

class scavenger_controller: public ship_controller {
private:
    SCAVENGER_STATES current_state;
    glm::vec2 wander_target;

public:
    scavenger_controller();
    void update(float dt) override;
    void on_damage(game_entity &other, int amount) override;
    void change_state(SCAVENGER_STATES state);
};

#endif //SINISTAR_SCAVENGER_CONTROLLER_H

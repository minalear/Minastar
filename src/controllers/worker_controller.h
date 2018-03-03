//
// Created by Trevor Fisher on 2/21/2018.
//

#ifndef SINISTAR_WORKER_CONTROLLER_H
#define SINISTAR_WORKER_CONTROLLER_H

#include "ship_controller.h"

enum struct WORKER_STATES {
    Mining, //Seeking and mining asteroids
    Deliver, //Delivering resources to Sinistar
    Return, //Returning to their old mining position
    Flee, //Fleeing from Player (calling for soldier support)
};

class worker_controller: public ship_controller {
private:
    WORKER_STATES current_state;
    glm::vec2 saved_pos;

public:
    worker_controller();
    void update(float dt) override;
    void on_damage(game_entity &other, int amount) override;
    void change_state(WORKER_STATES state);
};

#endif //SINISTAR_WORKER_CONTROLLER_H

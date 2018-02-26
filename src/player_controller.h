//
// Created by Trevor Fisher on 2/20/2018.
//

#ifndef SINISTAR_PLAYER_CONTROLLER_H
#define SINISTAR_PLAYER_CONTROLLER_H

#include "ship_controller.h"

class player_controller: public ship_controller {
private:
    float healing_timer = 0.f;

public:
    player_controller();
    void update(float dt) override;
    void on_damage(class game_entity &other, int amount) override;
};


#endif //SINISTAR_PLAYER_CONTROLLER_H

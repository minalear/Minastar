//
// Created by minalear on 2/9/2018.
//

#ifndef SINISTAR_SHIP_H
#define SINISTAR_SHIP_H

#include "game_entity.h"

class ship: public game_entity {
public:
    class ship_controller *controller;

    int mineral_count;

    ship(ship_controller *controller, ENTITY_TYPES ship_type);
    void update(float dt) override;
    void handle_collision(game_entity &other, glm::vec2 point) override;
    void damage(game_entity &other, int amount) override;
    void send_message(MESSAGE_TYPES message, game_entity &sender) override;
};


#endif //SINISTAR_SHIP_H

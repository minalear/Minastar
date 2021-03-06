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
    int shield, max_shield;
    float boost, max_boost;

    ship(ship_controller *controller, ENTITY_TYPES ship_type);
    void update(float dt) override;
    void handle_collision(game_entity &other, glm::vec2 point) override;
    void damage(game_entity &other, int amount) override;
    void send_message(MESSAGE_TYPES message, game_entity &sender) override;
    void set_shield(int amount);
    void modify_shield(int amount);
    void set_boost(float amount);
    void modify_boost(float amount);
};


#endif //SINISTAR_SHIP_H

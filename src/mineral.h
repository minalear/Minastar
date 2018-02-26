//
// Created by Trevor Fisher on 2/20/2018.
//

#ifndef SINISTAR_MINERAL_H
#define SINISTAR_MINERAL_H

#include "game_entity.h"
#include "glm.hpp"

class mineral: public game_entity {
public:
    mineral(glm::vec2 pos, glm::vec2 vel);
    void update(float dt) override;
    void handle_collision(game_entity &other, glm::vec2 point) override;
};

#endif //SINISTAR_MINERAL_H
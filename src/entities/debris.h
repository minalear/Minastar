//
// Created by Trevor Fisher on 3/3/2018.
//

#ifndef SINISTAR_DEBRIS_H
#define SINISTAR_DEBRIS_H

#include "game_entity.h"
#include "glm.hpp"

class debris: public game_entity {
private:
    float life_timer;

public:
    debris(glm::vec2 pos, glm::vec2 center, glm::vec2 vel);
    void update(float dt) override;
    void handle_collision(game_entity &other, glm::vec2 point) override;
};

#endif //SINISTAR_DEBRIS_H

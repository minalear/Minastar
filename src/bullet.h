//
// Created by minalear on 2/13/2018.
//

#ifndef SINISTAR_BULLET_H
#define SINISTAR_BULLET_H

#include "game_entity.h"

class bullet: public game_entity {
public:
    bullet(glm::vec2 pos, glm::vec2 vel);
    void update(float dt) override;
    void handle_collision(const game_entity &other, glm::vec2 point) override;
};


#endif //SINISTAR_BULLET_H

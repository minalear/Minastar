//
// Created by Trevor Fisher on 2/8/2018.
//

#ifndef SINISTAR_ASTEROID_H
#define SINISTAR_ASTEROID_H

#include "game_entity.h"

class asteroid: public game_entity {
public:
    asteroid();
    asteroid(glm::vec2 pos);
    asteroid(float size, glm::vec2 pos);
    void update(float dt) override;
    void handle_collision(game_entity &other, glm::vec2 point) override;
    void damage(game_entity &other, int damage) override;
};


#endif //SINISTAR_ASTEROID_H

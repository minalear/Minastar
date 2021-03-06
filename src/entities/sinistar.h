//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_SINISTAR_H
#define SINISTAR_SINISTAR_H

#include "game_entity.h"

class sinistar: public game_entity {
private:
    float quote_timer = 0.f;

public:
    sinistar(glm::vec2 pos);
    void update(float dt) override;
    void handle_collision(game_entity &other, glm::vec2 point) override;
};


#endif //SINISTAR_SINISTAR_H

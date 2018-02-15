//
// Created by Trevor Fisher on 2/15/2018.
//

#ifndef SINISTAR_SINIBOMB_H
#define SINISTAR_SINIBOMB_H

#include "game_entity.h"

class sinibomb: public game_entity {
public:
    sinibomb(glm::vec2 pos);
    void update(float dt) override;
    void handle_collision(const game_entity &other) override;
};


#endif //SINISTAR_SINIBOMB_H

//
// Created by Trevor Fisher on 2/8/2018.
//

#ifndef SINISTAR_ASTEROID_H
#define SINISTAR_ASTEROID_H

#include "game_entity.h"

class asteroid: public game_entity {
public:
    asteroid();
    void update(float dt);
};


#endif //SINISTAR_ASTEROID_H

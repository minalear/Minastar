//
// Created by minalear on 2/9/2018.
//

#ifndef SINISTAR_SHIP_H
#define SINISTAR_SHIP_H

#include "game_entity.h"

class ship: public game_entity {
public:
    ship();
    void update(float dt) override ;
};


#endif //SINISTAR_SHIP_H

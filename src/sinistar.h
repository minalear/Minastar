//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_SINISTAR_H
#define SINISTAR_SINISTAR_H

#include "game_entity.h"

class sinistar: public game_entity {
public:
    sinistar();
    void update(float dt) override;
};


#endif //SINISTAR_SINISTAR_H

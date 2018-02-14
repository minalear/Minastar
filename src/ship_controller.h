//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_SHIP_CONTROLLER_H
#define SINISTAR_SHIP_CONTROLLER_H

#include "ship.h"

class ship_controller {
public:
    ship *owner;

    ship_controller(ship *owner);

    virtual void update(float dt);
    void fire_bullet();
};


#endif //SINISTAR_SHIP_CONTROLLER_H

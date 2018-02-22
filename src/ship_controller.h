//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_SHIP_CONTROLLER_H
#define SINISTAR_SHIP_CONTROLLER_H

#include "glm.hpp"

class ship_controller {
public:
    class ship *owner;

    ship_controller();
    virtual void update(float dt);
    void shoot(glm::vec2 pos, glm::vec2 vel);
};


#endif //SINISTAR_SHIP_CONTROLLER_H

//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_SHIP_CONTROLLER_H
#define SINISTAR_SHIP_CONTROLLER_H


class ship_controller {
public:
    class ship *owner;

    ship_controller();
    virtual void update(float dt);
};


#endif //SINISTAR_SHIP_CONTROLLER_H

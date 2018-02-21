//
// Created by Trevor Fisher on 2/21/2018.
//

#ifndef SINISTAR_WORKER_CONTROLLER_H
#define SINISTAR_WORKER_CONTROLLER_H

#include "ship_controller.h"

class worker_controller: public ship_controller {
public:
    worker_controller();
    void update(float dt) override;
};


#endif //SINISTAR_WORKER_CONTROLLER_H

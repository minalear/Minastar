//
// Created by Trevor Fisher on 3/1/2018.
//

#ifndef SINISTAR_START_SCREEN_H
#define SINISTAR_START_SCREEN_H

#include "screen.h"

class start_screen: public screen {
    void update(float dt) override;
    void draw() override;
};

#endif //SINISTAR_START_SCREEN_H

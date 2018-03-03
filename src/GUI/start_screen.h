//
// Created by Trevor Fisher on 3/1/2018.
//

#ifndef SINISTAR_START_SCREEN_H
#define SINISTAR_START_SCREEN_H

#include "screen.h"

class start_screen: public screen {
public:
    start_screen(screen_manager *manager);

    void update(float dt) override;
    void draw() override;

    void on_activate() override;
};

#endif //SINISTAR_START_SCREEN_H

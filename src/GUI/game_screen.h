//
// Created by Trevor Fisher on 3/1/2018.
//

#ifndef SINISTAR_GAME_SCREEN_H
#define SINISTAR_GAME_SCREEN_H

#include "screen.h"

class game_screen: public screen {
public:
    game_screen();
    void update(float dt) override;
    void draw() override;
};

#endif //SINISTAR_GAME_SCREEN_H

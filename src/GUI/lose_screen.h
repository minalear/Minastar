//
// Created by Trevor Fisher on 3/3/2018.
//

#ifndef SINISTAR_LOSE_SCREEN_H
#define SINISTAR_LOSE_SCREEN_H

#include "screen.h"
#include "glm.hpp"

class lose_screen: public screen {
private:
    glm::vec2 text_size;

public:
    lose_screen(screen_manager *manager);

    void update_fixed(float dt) override;
    void update_realtime() override;
    void draw() override;
};

#endif //SINISTAR_LOSE_SCREEN_H

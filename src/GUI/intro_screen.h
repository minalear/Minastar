//
// Created by Trevor Fisher on 3/2/2018.
//

#ifndef SINISTAR_INTRO_SCREEN_H
#define SINISTAR_INTRO_SCREEN_H

#include "glm.hpp"
#include "screen.h"

class intro_screen: public screen {
private:
    glm::vec2 text_size;

public:
    intro_screen(screen_manager *manager);

    void update(float dt) override;
    void draw() override;

    void on_activate() override;
    void on_deactivate() override;
};

#endif //SINISTAR_INTRO_SCREEN_H

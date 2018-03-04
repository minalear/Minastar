//
// Created by Trevor Fisher on 3/3/2018.
//

#ifndef SINISTAR_VICTORY_SCREEN_H
#define SINISTAR_VICTORY_SCREEN_H

#include "screen.h"
#include "glm.hpp"

class victory_screen: public screen {
private:
    glm::vec2 text_size, credits_size;
    float credits_timer;
    bool move_text;

public:
    victory_screen(screen_manager *manager);

    void update(float dt) override;
    void draw() override;

    void on_activate() override;
    void on_deactivate() override;
};

#endif //SINISTAR_VICTORY_SCREEN_H

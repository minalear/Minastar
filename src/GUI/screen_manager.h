//
// Created by Trevor Fisher on 3/1/2018.
//

#ifndef SINISTAR_SCREEN_MANAGER_H
#define SINISTAR_SCREEN_MANAGER_H

#include <unordered_map>
#include "screen.h"

class screen_manager {
private:
    std::unordered_map<std::string, screen*> screens;
    screen *active_screen;

public:
    screen_manager();
    ~screen_manager();

    void attach_screen(const std::string name, screen *screen);
    void switch_screen(const std::string name);

    void update_active_screen(float dt);
    void draw_active_screen();
};

#endif //SINISTAR_SCREEN_MANAGER_H

//
// Created by Trevor Fisher on 3/1/2018.
//

#ifndef SINISTAR_SCREEN_MANAGER_H
#define SINISTAR_SCREEN_MANAGER_H

#include <unordered_map>
#include "../engine/shader_program.h"
#include "text_renderer.h"
#include "bar_renderer.h"
#include "screen.h"

class screen_manager {
private:
    std::unordered_map<std::string, screen*> screens;
    screen *active_screen;

public:
    minalear::shader_program *shape_shader, *text_shader;

    bar_renderer *bar_render;
    text_renderer *text_render;

    screen_manager();
    ~screen_manager();

    void attach_screen(const std::string name, screen *screen);
    void switch_screen(const std::string name);

    void update_fixed(float dt);
    void update_realtime();
    void draw_active_screen();
};

#endif //SINISTAR_SCREEN_MANAGER_H

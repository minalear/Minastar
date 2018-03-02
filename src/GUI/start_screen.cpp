//
// Created by Trevor Fisher on 3/1/2018.
//

#include "start_screen.h"
#include "../engine/window.h"
#include "../engine/input.h"
#include "screen_manager.h"

glm::vec2 title_size, instr_size;

start_screen::start_screen(screen_manager *manager) : screen(manager) {
    title_size = manager->text_render->measure_string("SINISTAR", glm::vec2(1.f));
    instr_size = manager->text_render->measure_string("Press X to continue", glm::vec2(0.35f));
}
void start_screen::update(float dt) {
    if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::A)) {
        manager->switch_screen("Game");
    }
}
void start_screen::draw() {
    int window_width  = minalear::get_window_width();
    int window_height = minalear::get_window_height();

    glm::vec2 title_pos = glm::vec2(window_width / 2.f, window_height / 2.f);
    glm::vec2 instr_pos = glm::vec2(title_pos.x, title_pos.y + manager->text_render->text_font->common.line_height);

    title_pos -= title_size / 2.f;
    instr_pos -= instr_size / 2.f;

    manager->text_shader->use();
    manager->text_render->draw_string(manager->text_shader, "SINISTAR",            title_pos, glm::vec2(1.f));
    manager->text_render->draw_string(manager->text_shader, "Press X to continue", instr_pos, glm::vec2(0.35f));
}
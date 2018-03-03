//
// Created by Trevor Fisher on 3/3/2018.
//

#include "lose_screen.h"
#include "../engine/window.h"
#include "../engine/input.h"
#include "screen_manager.h"

lose_screen::lose_screen(screen_manager *manager) : screen(manager) {
    text_size = manager->text_render->measure_string("You lose!", glm::vec2(1.f));
}
void lose_screen::update(float dt) {
    if (minalear::was_button_up(minalear::JOYSTICK_BUTTONS::A)) {
        manager->switch_screen("Start");
    }
}
void lose_screen::draw() {
    int window_width  = minalear::get_window_width();
    int window_height = minalear::get_window_height();

    glm::vec2 text_pos = glm::vec2(window_width / 2.f, window_height / 2.f);

    text_pos -= text_size / 2.f;

    manager->text_shader->use();
    manager->text_render->draw_string(manager->text_shader, "You lose!", text_pos, glm::vec2(1.f));
}
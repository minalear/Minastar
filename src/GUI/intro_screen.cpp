//
// Created by Trevor Fisher on 3/2/2018.
//

#include "intro_screen.h"
#include "../engine/window.h"
#include "../engine/input.h"
#include "../engine/audio_player.h"
#include "screen_manager.h"

const std::string INTRO_TEXT =
        "The year is 2007 AD.  A threat from space,\n"
        "known only as Minastar, is being constructed\n"
        "to destroy the Earth.\n"
        "You are Avery Johnson Vangootson, \n"
        "the son of the legendary Zache Vangootson,\n"
        "and you are tasked with dealing with this threat.\n"
        "Defeat Minastar or perish!";

intro_screen::intro_screen(screen_manager *manager) : screen(manager) {
    text_size = manager->text_render->measure_string(INTRO_TEXT, glm::vec2(0.5f));
}

void intro_screen::update_fixed(float dt) { }
void intro_screen::update_realtime() {
    if (minalear::was_button_up(minalear::JOYSTICK_BUTTONS::A)) {
        manager->switch_screen("Game");
    }
}
void intro_screen::draw() {
    int window_height = minalear::get_window_height();

    glm::vec2 text_pos = glm::vec2(10.f, window_height / 2.f - text_size.y / 2.f);

    manager->text_shader->use();
    manager->text_render->draw_string(manager->text_shader, INTRO_TEXT, text_pos, glm::vec2(0.5f));
}

void intro_screen::on_activate() {
    minalear::audio_engine.play_song("story_music", true);
}
void intro_screen::on_deactivate() {
    minalear::audio_engine.stop_song("story_music");
}
//
// Created by Trevor Fisher on 3/3/2018.
//

#include "victory_screen.h"
#include "../engine/window.h"
#include "../engine/input.h"
#include "../engine/audio_player.h"
#include "screen_manager.h"

const std::string CREDITS_TEXT =
        "Minastar inspired by arcade classic Sinistar.\n\n"
                "Copyright Williams Electronics 1983 - 2018\n\n\n"

                "Programmer/Desinger Trevor Fisher\n\n\n\n\n"

                "Music\n\n"
                "\"Escaping the Collapsing Universe\" by Komiku\n\n"
                "http://loyaltyfreakmusic.com/\n\n\n\n"

                "\"Big Crumble\" by Komiku\n\n"
                "http://loyaltyfreakmusic.com/\n\n\n\n"

                "\"The Great Madeja\" by Rolemusic\n\n"
                "http://rolemusic.sawsquarenoise.com/\n\n\n\n"

                "Special Thanks To\n\n"
                "Max aka Flinnan\n\n\n\n"
                "The other Trevor\n\n\n\n"
                "Zache Vangootson\n\n\n\n"
                "Jack Black\n\n\n\n"
                "Santa Claus\n\n\n\n"
                "Every Airbud Movie\n\n\n\n"
                "Professor Kaiju\n\n\n\n"
                "$$$ MONEY $$$\n\n\n\n"
                "Not my mother\n\n\n\n"
                "jk I love u mom\n\n\n\n"
                "The X-Men movies\n\n\n\n"
                "everything else that I forgot"

                "\n\n\n\n\n\n\n\n\n\n\n\n"
                "\n\n\n\n\n\n\n\n\n\n\n\n"
                "Thanks for playing my dude";

victory_screen::victory_screen(screen_manager *manager) : screen(manager) {
    text_size    = manager->text_render->measure_string("You win!", glm::vec2(1.f));
    credits_size = manager->text_render->measure_string(CREDITS_TEXT, glm::vec2(0.5f));

    credits_timer = 0.f;
    move_text = false;
}

void victory_screen::update(float dt) {
    if (minalear::was_button_up(minalear::JOYSTICK_BUTTONS::A)) {
        manager->switch_screen("Start");
    }

    credits_timer += dt;
    if (credits_timer >= 4.f && !move_text) {
        move_text = true;
    }
    else if (credits_timer >= 220.f) {
        manager->switch_screen("Start");
    }
}
void victory_screen::draw() {
    int window_width  = minalear::get_window_width();
    int window_height = minalear::get_window_height();

    glm::vec2 text_pos = glm::vec2(window_width / 2.f, window_height / 2.f);
    glm::vec2 cred_pos = glm::vec2(10.f, window_height + 10.f);
    text_pos -= text_size / 2.f;

    if (move_text) {
        float pos_adjust = (credits_timer - 4.f) * 10.f;

        text_pos.y -= pos_adjust;
        cred_pos.y -= pos_adjust;
    }

    manager->text_shader->use();
    manager->text_render->draw_string(manager->text_shader, "You win!", text_pos, glm::vec2(1.f));
    manager->text_render->draw_string(manager->text_shader, CREDITS_TEXT, cred_pos, glm::vec2(0.5f));
}

void victory_screen::on_activate() {
    minalear::audio_engine.play_song("credits_music", false);
}
void victory_screen::on_deactivate() {
    minalear::audio_engine.stop_song("credits_music");
}
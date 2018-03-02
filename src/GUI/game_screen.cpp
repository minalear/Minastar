//
// Created by Trevor Fisher on 3/1/2018.
//

#include "game_screen.h"
#include "../engine/window.h"
#include "screen_manager.h"
#include "gtc/matrix_transform.hpp"
#include "../world.h"
#include "../entities/ship.h"
#include "../campaign.h"

world game_world;
ship *player_ship;

game_screen::game_screen(screen_manager *manager) : screen(manager) { }

void game_screen::on_activate() {
    game_world.reset();
    campaign.reset();

    game_world.generate_game_world();
    game_world.generate_buffer_data();

    campaign.init(&game_world);

    player_ship = (ship*)game_world.find_entity(ENTITY_TYPES::Player);
}

void game_screen::update(float dt) {
    game_world.update(dt);
    campaign.update();
}
void game_screen::draw() {
    //Setup game camera
    float camera_zoom = 0.8f;
    glm::vec2 cam_pos = glm::vec2(-player_ship->position.x + (minalear::get_window_width() / 2.f) / camera_zoom,
                                  -player_ship->position.y + (minalear::get_window_height() / 2.f) / camera_zoom);
    glm::mat4 view    = glm::scale(glm::mat4(1.f), glm::vec3(camera_zoom)) *
                        glm::translate(glm::mat4(1.f), glm::vec3(cam_pos, 0.f));

    //Set matrix values
    manager->shape_shader->use();
    manager->shape_shader->set_view_mat4(view);

    //Draw the game world
    game_world.draw(manager->shape_shader);

    //Draw UI
    manager->shape_shader->set_view_mat4(glm::mat4(1.f));
    manager->bar_render->draw_bar(manager->shape_shader,
                         player_ship->health,
                         player_ship->max_health,
                         glm::vec2(10.f, 40.f), glm::vec2(100.f, 12.f),
                         glm::vec3(141 / 255.f, 198 / 255.f,  63 / 255.f),
                         glm::vec3( 71 / 255.f,  75 / 255.f,  65 / 255.f));
    manager->bar_render->draw_bar(manager->shape_shader,
                         campaign.sinistar_entity->health,
                         campaign.sinistar_entity->max_health,
                         glm::vec2(10.f, 56.f), glm::vec2(100.f, 12.f),
                         glm::vec3(198 / 255.f,  63 / 255.f,  63 / 255.f),
                         glm::vec3(116 / 255.f,  59 / 255.f,  59 / 255.f));
    manager->shape_shader->set_view_mat4(view);

    std::string ui_text = "minerals " + std::to_string(player_ship->mineral_count) + "\n" +
                          "debug " + std::to_string(campaign.worker_mineral_count);

    manager->text_shader->use();
    manager->text_render->draw_string(manager->text_shader, ui_text, glm::vec2(10.f), glm::vec2(0.4f));
}
//
// Created by Trevor Fisher on 3/1/2018.
//

#include "screen_manager.h"
#include "../engine/file_handler.h"
#include "gtc/matrix_transform.hpp"
#include "start_screen.h"
#include "game_screen.h"
#include "intro_screen.h"
#include "lose_screen.h"
#include "victory_screen.h"

screen_manager::screen_manager() {
    //Initialize shader programs
    shape_shader = new minalear::shader_program(
            minalear::read_file("shaders/basic_vert.glsl"),
            minalear::read_file("shaders/basic_frag.glsl"));
    shape_shader->use();
    shape_shader->init_uniforms();

    text_shader = new minalear::shader_program(
            minalear::read_file("shaders/text_vert.glsl"),
            minalear::read_file("shaders/text_frag.glsl"));
    text_shader->use();
    text_shader->init_uniforms();

    //Initialize matrices
    glm::mat4 proj, view, model;
    proj  = glm::ortho(0.f, 800.f, 450.f, 0.f, -1.f, 1.f);
    view  = glm::mat4(1.f);
    model = glm::mat4(1.f);

    shape_shader->use();
    shape_shader->set_proj_mat4(proj);
    shape_shader->set_view_mat4(view);
    shape_shader->set_model_mat4(model);

    text_shader->use();
    text_shader->set_proj_mat4(proj);
    text_shader->set_view_mat4(view);
    text_shader->set_model_mat4(model);

    //Initialize renderers
    bar_render = new bar_renderer;
    text_render = new text_renderer("Main");

    attach_screen("Start", new start_screen(this));
    attach_screen("Game", new game_screen(this));
    attach_screen("Intro", new intro_screen(this));
    attach_screen("Lose", new lose_screen(this));
    attach_screen("Victory", new victory_screen(this));

    active_screen = nullptr;
}
screen_manager::~screen_manager() {
    delete shape_shader;
    delete text_shader;
    delete bar_render;
    delete text_render;
}

void screen_manager::attach_screen(const std::string name, screen *screen) {
    screen->manager = this;
    screens.insert({ name, screen });
}
void screen_manager::switch_screen(const std::string name) {
    //Ensure the index is contained in the map
    auto index = screens.find(name);
    if (index != screens.end()) {

        if (active_screen)
            active_screen->on_deactivate();
        active_screen = index->second;
        active_screen->on_activate();
    }

    active_screen = screens[name];
}

void screen_manager::update_fixed(float dt) {
    active_screen->update_fixed(dt);
}
void screen_manager::update_realtime() {
    active_screen->update_realtime();
}
void screen_manager::draw_active_screen() {
    active_screen->draw();
}
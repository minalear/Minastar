#include <random>
#include <ctime>
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/vec1.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "engine/file_handler.h"
#include "engine/window.h"
#include "engine/shader_program.h"
#include "engine/input.h"
#include "engine/font.h"
#include "text_renderer.h"
#include "bar_renderer.h"
#include "world.h"
#include "ship.h"
#include "player_controller.h"
#include "campaign.h"

int main(int argc, char *argv[]) {
    //Either handle collision so they don't clump on top (preferred) or don't have allied bullets collide with allies

    //Initialize SDL and OpenGL
    minalear::init_game_window(800, 450);
    minalear::init_opengl();

    //Setup OpenGL settings
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

    //glEnable(GL_LINE_SMOOTH);
    //glEnable(GL_POLYGON_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Seed random number generator
    srand((unsigned int)time(NULL));

    //Setup game world
    world game_world;

    ship player_ship(new player_controller, ENTITY_TYPES::Player);
    player_ship.position = glm::vec2(WORLD_SIZE / 2.f);

    game_world.add_entity(&player_ship);

    game_world.generate_game_world();
    game_world.generate_buffer_data();

    campaign.init(&game_world);

    //Initialize shader programs
    minalear::shader_program game_shader(
            minalear::read_file("shaders/basic_vert.glsl"),
            minalear::read_file("shaders/basic_frag.glsl"));
    game_shader.use();
    game_shader.init_uniforms();

    minalear::shader_program text_shader(
            minalear::read_file("shaders/text_vert.glsl"),
            minalear::read_file("shaders/text_frag.glsl"));
    text_shader.use();
    text_shader.init_uniforms();

    //Initialize matrices
    glm::mat4 proj, view, model;
    proj  = glm::ortho(0.f, 800.f, 450.f, 0.f, -1.f, 1.f);
    view  = glm::mat4(1.f);
    model = glm::mat4(1.f);

    game_shader.use();
    game_shader.set_proj_mat4(proj);
    game_shader.set_view_mat4(view);
    game_shader.set_model_mat4(model);

    text_shader.use();
    text_shader.set_proj_mat4(proj);
    text_shader.set_view_mat4(view);
    text_shader.set_model_mat4(model);

    //Text renderer
    text_renderer text_renderer("main");
    bar_renderer bar_renderer;

    //Setup controller input
    minalear::init_input();

    //Time accumulator
    double time_accumulator = 0.f;

    //Begin main game loop
    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            //Break out of game loop
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        minalear::handle_input();

        //Accumulate time and update logic if past the desired accumulation time
        time_accumulator += minalear::dt();

        const float CONST_DT = 0.016f;
        if (time_accumulator >= CONST_DT) {
            //player_controller.update(CONST_DT);
            game_world.update(CONST_DT);
            campaign.update();

            time_accumulator = 0.f;
        }

        //Draw the game world
        game_shader.use();
        float camera_zoom = 1.f;
        glm::vec2 cam_pos = glm::vec2(-player_ship.position.x + (minalear::get_window_width() / 2.f) / camera_zoom,
                                      -player_ship.position.y + (minalear::get_window_height() / 2.f) / camera_zoom);
        view = glm::scale(glm::mat4(1.f), glm::vec3(camera_zoom)) *
               glm::translate(glm::mat4(1.f), glm::vec3(cam_pos, 0.f));
        game_shader.set_view_mat4(view);
        game_world.draw(&game_shader);

        //Draw UI
        game_shader.set_view_mat4(glm::mat4(1.f));
        bar_renderer.draw_bar(&game_shader,
                              campaign.sinistar_entity->health,
                              campaign.sinistar_entity->max_health,
                              glm::vec2(10.f, 40.f), glm::vec2(100.f, 18.f),
                              glm::vec3(227 / 255.f, 68 / 255.f, 68 / 255.f),
                              glm::vec3(100 / 255.f, 59 / 255.f, 59 / 255.f));
        game_shader.set_view_mat4(view);

        std::string ui_text = "minerals " + std::to_string(player_ship.mineral_count) + "\n" +
                              "debug " + std::to_string(campaign.worker_mineral_count);

        text_shader.use();
        text_renderer.draw_string(&text_shader, ui_text, glm::vec2(10.f), glm::vec2(0.4f));

        minalear::swap_buffers();

        //SDL_PumpEvents(); //Not sure if this is exactly required
        SDL_FlushEvent(SDL_JOYAXISMOTION);
    } //end main game loop

    minalear::window_cleanup();
    return 0;
}
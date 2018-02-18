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
#include "world.h"
#include "asteroid.h"
#include "ship.h"
#include "ship_controller.h"
#include "sinistar.h"

const int NUM_ASTEROIDS = 6;
const int NUM_SHIPS = 1;

int main(int argc, char *argv[]) {
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

    world game_world;

    //Create game entities
    asteroid asteroids[NUM_ASTEROIDS];
    ship ships[NUM_SHIPS];

    ship_controller player_controller(&ships[0]);

    game_world.add_entities(asteroids, NUM_ASTEROIDS);
    game_world.add_entities(ships, NUM_SHIPS);
    game_world.add_entity(new sinistar);

    game_world.generate_buffer_data();

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
    //text_renderer text_renderer("main");

    //Setup controller input
    minalear::init_input();

    int frame_count = 0, fps = 0;
    float current_time = 0.f;
    float last_time = SDL_GetTicks();

    //Begin main game loop
    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            //Break out of game loop
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        float dt = minalear::dt();
        minalear::handle_input();

        glClear(GL_COLOR_BUFFER_BIT);

        player_controller.update(dt);

        game_shader.use();
        game_world.update(dt);
        game_world.draw(&game_shader);

        //text_shader.use();
        //text_renderer.draw_string(&text_shader, "fps " + std::to_string(fps), glm::vec2(10.f), glm::vec2(0.4f));

        minalear::swap_buffers();

        //TODO: look into laggy joystick input
        SDL_FlushEvent(SDL_JOYAXISMOTION);

        //Calculate FPS
        frame_count++;
        current_time = SDL_GetTicks();
        if (current_time > last_time + 1000.f) {
            fps = frame_count;
            frame_count = 0;

            last_time = current_time;
        }
    } //end main game loop

    return 0;
}
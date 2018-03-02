#include <random>
#include <ctime>
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "glm.hpp"
#include "engine/file_handler.h"
#include "engine/window.h"
#include "engine/shader_program.h"
#include "engine/input.h"
#include "engine/font.h"
#include "GUI/screen_manager.h"

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

    //Setup controller input
    minalear::init_input();

    //Screen Manager
    screen_manager screen_manager;
    screen_manager.switch_screen("Game");

    //For having consistent dts for update functions
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

        //Update if time_accumulator is past the threshold
        const float CONST_DT = 0.016f;
        if (time_accumulator >= CONST_DT) {
            screen_manager.update_active_screen(CONST_DT);
            time_accumulator = 0.f;
        }

        //Accumulate time and update logic if past the desired accumulation time
        time_accumulator += minalear::dt();

        screen_manager.draw_active_screen();

        minalear::swap_buffers();

        //SDL_PumpEvents(); //Not sure if this is exactly required
        SDL_FlushEvent(SDL_JOYAXISMOTION);
    } //end main game loop

    minalear::window_cleanup();
    return 0;
}
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
#include "engine/audio_player.h"
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

    //Load audio files
    minalear::audio_engine.register_audio_file("fight_music",   "audio/fight_komiku.ogg");
    minalear::audio_engine.register_audio_file("story_music",   "audio/story_komiku.ogg");
    minalear::audio_engine.register_audio_file("credits_music", "audio/credits_rolemusic.ogg");

    minalear::audio_engine.register_audio_file("player_shot", "audio/shot.wav");
    minalear::audio_engine.register_audio_file("explosion",   "audio/explosion.wav");
    minalear::audio_engine.register_audio_file("missile",     "audio/missile.wav");
    minalear::audio_engine.register_audio_file("boost",       "audio/boost.wav");
    minalear::audio_engine.register_audio_file("pickup",      "audio/pickup.wav");

    //RUN COWARD
    minalear::audio_engine.register_audio_file("sinistar_greeting",      "audio/sinistar.wav");
    minalear::audio_engine.register_audio_file("sinistar_beware_coward", "audio/beware_coward.wav");
    minalear::audio_engine.register_audio_file("sinistar_i_live",        "audio/beware_i_live.wav");
    minalear::audio_engine.register_audio_file("sinistar_hunger",        "audio/i_hunger.wav");
    minalear::audio_engine.register_audio_file("sinistar_rawr",          "audio/rawr.wav");
    minalear::audio_engine.register_audio_file("sinistar_run_coward",    "audio/run_coward.wav");
    minalear::audio_engine.register_audio_file("sinistar_run",           "audio/run_run_run.wav");

    //Screen Manager
    screen_manager screen_manager;
    screen_manager.switch_screen("Start");

    //For having consistent dts for update_fixed functions
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

        //Accumulate time and update_fixed logic if past the accumulation time threshold (16ms = 60fps)
        time_accumulator += minalear::dt();

        const float CONST_DT = 0.016f;
        if (time_accumulator >= CONST_DT) {
            screen_manager.update_fixed(CONST_DT);
            time_accumulator = 0.f;
        }

        screen_manager.update_realtime();
        screen_manager.draw_active_screen();

        minalear::swap_buffers();

        //SDL_PumpEvents(); //Not sure if this is exactly required
        SDL_FlushEvent(SDL_JOYAXISMOTION);
    } //end main game loop

    minalear::window_cleanup();
    return 0;
}
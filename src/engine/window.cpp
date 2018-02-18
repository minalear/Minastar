//
// Created by Trevor Fisher on 2/3/2018.
//

#include <iostream>
#include <cassert>
#include "window.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"

#define PC_BUILD

#ifdef LAPTOP_BUILD
const int OPENGL_MAJOR_VERSION = 3;
const int OPENGL_MINOR_VERSION = 1;
#endif
#ifdef PC_BUILD
const int OPENGL_MAJOR_VERSION = 4;
const int OPENGL_MINOR_VERSION = 0;
#endif

SDL_Window* window;
SDL_GLContext context;

uint32_t start_time;

void minalear::init_game_window(const int windowWidth, const int windowHeight) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);

    //TODO: Vsync option doesn't seem to affect PC Workstation
    //SDL_GL_SetSwapInterval(0);

    window = SDL_CreateWindow("Sinistar",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowWidth, windowHeight,
                              SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);
    start_time = SDL_GetTicks();
}

void minalear::init_opengl() {
    int success = gladLoadGLLoader(SDL_GL_GetProcAddress);
    assert(success);
}

void minalear::swap_buffers() {
    SDL_GL_SwapWindow(window);
}

float minalear::dt() {
    uint32_t ticks = SDL_GetTicks() - start_time;
    float dt = ticks * 0.001f;
    start_time = SDL_GetTicks();

    return dt;
}
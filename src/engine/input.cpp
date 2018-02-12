//
// Created by minalear on 2/9/2018.
//

#include "input.h"
#include "SDL2/SDL.h"
#include "vec2.hpp"

SDL_Joystick *main_joystick;
minalear::controller_state *main_controller_state;

const float JOYSTICK_LENGTH = SDL_JOYSTICK_AXIS_MAX;

void minalear::init_input() {
    SDL_JoystickEventState(SDL_ENABLE);
    main_joystick = SDL_JoystickOpen(0);

    main_controller_state = new minalear::controller_state;

    handle_input();
}

void minalear::handle_input() {
    main_controller_state->left_stick.x = SDL_JoystickGetAxis(main_joystick, 0) / JOYSTICK_LENGTH;
    main_controller_state->left_stick.y = SDL_JoystickGetAxis(main_joystick, 1) / JOYSTICK_LENGTH;
    main_controller_state->right_stick.x = SDL_JoystickGetAxis(main_joystick, 2) / JOYSTICK_LENGTH;
    main_controller_state->right_stick.y = SDL_JoystickGetAxis(main_joystick, 3) / JOYSTICK_LENGTH;

    main_controller_state->left_stick_length = main_controller_state->left_stick.length();
    main_controller_state->right_stick_length = main_controller_state->right_stick.length();
}

minalear::controller_state* minalear::get_controller_state() {
    return main_controller_state;
}
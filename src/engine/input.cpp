//
// Created by minalear on 2/9/2018.
//

#include <iostream>
#include "input.h"
#include "SDL2/SDL.h"
#include "glm.hpp"
#include "vec2.hpp"

SDL_Joystick *main_joystick;
minalear::controller_state *main_controller_ptr;

const float JOYSTICK_LENGTH = SDL_JOYSTICK_AXIS_MAX;

void minalear::init_input() {
    SDL_JoystickEventState(SDL_ENABLE);
    main_joystick = SDL_JoystickOpen(0);

    main_controller_ptr = new minalear::controller_state;

    handle_input();
}

void minalear::handle_input() {
    //Get the raw data for the left stick (each axis is bound between -1 and 1)
    glm::vec2 raw_left_stick = glm::vec2(
            SDL_JoystickGetAxis(main_joystick, 0) / JOYSTICK_LENGTH,
            SDL_JoystickGetAxis(main_joystick, 1) / JOYSTICK_LENGTH
    );

    //Set the length of our raw input, but clamped between 0 and 1
    main_controller_ptr->left_stick_length = glm::clamp(glm::length(raw_left_stick), 0.f, 1.f);

    //Normalize the left stick
    main_controller_ptr->left_stick = glm::normalize(raw_left_stick);
}

bool minalear::is_button_down(JOYSTICK_BUTTONS button) {
    return SDL_JoystickGetButton(main_joystick, (uint8_t)button);
}

minalear::controller_state* minalear::get_controller_ptr() {
    return main_controller_ptr;
}
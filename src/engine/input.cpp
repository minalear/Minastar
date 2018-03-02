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

const float AXIS_LENGTH = SDL_JOYSTICK_AXIS_MAX;
const float TRIGGER_BUTTON_MIN_VALUE = 0.85f;

const int LEFT_JOYSTICK_X_AXIS  = 0;
const int LEFT_JOYSTICK_Y_AXIS  = 1;
const int RIGHT_JOYSTICK_X_AXIS = 3;
const int RIGHT_JOYSTICK_Y_AXIS = 4;

const int LEFT_TRIGGER_AXIS  = 2;
const int RIGHT_TRIGGER_AXIS = 5;

void minalear::init_input() {
    SDL_JoystickEventState(SDL_ENABLE);
    main_joystick = SDL_JoystickOpen(0);

    main_controller_ptr = new minalear::controller_state;

    handle_input();
}

//TODO: Improve control handling (WasUp/Down etc.)
void minalear::handle_input() {
    //Get the raw data for the left stick (each axis is bound between -1 and 1)
    glm::vec2 raw_left_stick = glm::vec2(
            SDL_JoystickGetAxis(main_joystick, LEFT_JOYSTICK_X_AXIS) / AXIS_LENGTH,
            SDL_JoystickGetAxis(main_joystick, LEFT_JOYSTICK_Y_AXIS) / AXIS_LENGTH
    );
    glm::vec2 raw_right_stick = glm::vec2(
            SDL_JoystickGetAxis(main_joystick, RIGHT_JOYSTICK_X_AXIS) / AXIS_LENGTH,
            SDL_JoystickGetAxis(main_joystick, RIGHT_JOYSTICK_Y_AXIS) / AXIS_LENGTH
    );

    //Set the length of our raw input, but clamped between 0 and 1
    main_controller_ptr->left_stick_length  =  glm::clamp(glm::length(raw_left_stick), 0.f, 1.f);
    main_controller_ptr->right_stick_length = glm::clamp(glm::length(raw_right_stick), 0.f, 1.f);

    //Normalize the sticks
    main_controller_ptr->left_stick  =  glm::normalize(raw_left_stick);
    main_controller_ptr->right_stick = glm::normalize(raw_right_stick);

    //Get triggers (mapped 0 to 1)
    float raw_left_trigger  = (SDL_JoystickGetAxis(main_joystick, LEFT_TRIGGER_AXIS) + AXIS_LENGTH) / (2 * AXIS_LENGTH);
    float raw_right_trigger = (SDL_JoystickGetAxis(main_joystick, RIGHT_TRIGGER_AXIS) + AXIS_LENGTH) / (2 * AXIS_LENGTH);

    main_controller_ptr->left_trigger  = glm::clamp(raw_left_trigger, 0.f, 1.f);
    main_controller_ptr->right_trigger = glm::clamp(raw_right_trigger, 0.f, 1.f);
}

bool minalear::is_button_down(JOYSTICK_BUTTONS button) {
    //Triggers are special cases
    if (button == JOYSTICK_BUTTONS::L3) {
        return (main_controller_ptr->left_trigger >= TRIGGER_BUTTON_MIN_VALUE);
    }
    else if (button == JOYSTICK_BUTTONS::R3) {
        return (main_controller_ptr->right_trigger >= TRIGGER_BUTTON_MIN_VALUE);
    }

    return SDL_JoystickGetButton(main_joystick, (uint8_t)button);
}

minalear::controller_state* minalear::get_controller_ptr() {
    return main_controller_ptr;
}
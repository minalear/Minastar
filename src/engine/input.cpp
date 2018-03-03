//
// Created by minalear on 2/9/2018.
//

#include <iostream>
#include "input.h"
#include "SDL2/SDL.h"
#include "glm.hpp"
#include "vec2.hpp"

SDL_Joystick *main_joystick;
minalear::controller_state *this_state, *last_state;

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

    this_state = new minalear::controller_state;
    last_state = new minalear::controller_state;

    handle_input();
}

void minalear::handle_input() {
    (*last_state) = (*this_state);

    //Update button states
    for (int i = 0; i < NUM_JOYSTICK_BUTTONS; i++) {
        this_state->button_states[i] = SDL_JoystickGetButton(main_joystick, (uint8_t)i);
    }

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
    this_state->left_stick_length  =  glm::clamp(glm::length(raw_left_stick), 0.f, 1.f);
    this_state->right_stick_length = glm::clamp(glm::length(raw_right_stick), 0.f, 1.f);

    //Normalize the sticks
    this_state->left_stick  =  glm::normalize(raw_left_stick);
    this_state->right_stick = glm::normalize(raw_right_stick);

    //Get triggers (mapped 0 to 1)
    float raw_left_trigger  = (SDL_JoystickGetAxis(main_joystick, LEFT_TRIGGER_AXIS) + AXIS_LENGTH) / (2 * AXIS_LENGTH);
    float raw_right_trigger = (SDL_JoystickGetAxis(main_joystick, RIGHT_TRIGGER_AXIS) + AXIS_LENGTH) / (2 * AXIS_LENGTH);

    this_state->left_trigger  = glm::clamp(raw_left_trigger, 0.f, 1.f);
    this_state->right_trigger = glm::clamp(raw_right_trigger, 0.f, 1.f);
}

bool minalear::is_button_down(JOYSTICK_BUTTONS button) {
    //Triggers are special cases
    if (button == JOYSTICK_BUTTONS::L3) {
        return (this_state->left_trigger >= TRIGGER_BUTTON_MIN_VALUE);
    }
    else if (button == JOYSTICK_BUTTONS::R3) {
        return (this_state->right_trigger >= TRIGGER_BUTTON_MIN_VALUE);
    }

    return this_state->button_states[(int)button];
}

bool minalear::was_button_down(JOYSTICK_BUTTONS button) {
    return (this_state->button_states[(int)button] && !last_state->button_states[(int)button]);
}
bool minalear::was_button_up(JOYSTICK_BUTTONS button) {
    return (!this_state->button_states[(int)button] && last_state->button_states[(int)button]);
}

minalear::controller_state* minalear::get_controller_ptr() {
    return this_state;
}

void minalear::controller_state::operator= (const controller_state &c_state) {
    left_stick = c_state.left_stick;
    right_stick = c_state.left_stick;

    left_stick_length = c_state.left_stick_length;
    right_stick_length = c_state.left_stick_length;

    left_trigger = c_state.left_trigger;
    right_trigger = c_state.right_trigger;

    for (int i = 0; i < NUM_JOYSTICK_BUTTONS; i++) {
        button_states[i] = c_state.button_states[i];
    }
}
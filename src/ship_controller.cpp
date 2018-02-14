//
// Created by Trevor Fisher on 2/13/2018.
//

#include "ship_controller.h"
#include "engine/input.h"

ship_controller::ship_controller(ship *owner) {
    this->owner = owner;
}
void ship_controller::update(float dt) {
    minalear::controller_state *joystick = minalear::get_controller_ptr();

    if (joystick->left_stick_length > 0.15f) {
        float PLAYER_FORCE_FACTOR = 10.f * joystick->left_stick_length;
        owner->apply_force(joystick->left_stick * PLAYER_FORCE_FACTOR);
        owner->rotation = atan2f(joystick->left_stick.y, joystick->left_stick.x);
    }
}
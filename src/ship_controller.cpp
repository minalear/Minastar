//
// Created by Trevor Fisher on 2/13/2018.
//

#include "ship_controller.h"
#include "bullet.h"
#include "engine/input.h"
#include "world.h"

float bullet_timer = 0.f;
const float BULLET_FIRE_RATE = 1.f;

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

    bullet_timer = glm::clamp(bullet_timer - dt, 0.f, bullet_timer);
    if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::X) && bullet_timer <= 0.f) {
        bullet_timer = BULLET_FIRE_RATE;

        glm::vec2 bullet_velocity = glm::vec2(1.f);
        bullet_velocity.x = cosf(owner->rotation);
        bullet_velocity.y = sinf(owner->rotation);

        owner->game_world->add_entity(new bullet(owner->position, bullet_velocity * 10.f));
    }
}
void ship_controller::fire_bullet() {
    glm::vec2 direction = glm::vec2(0.f);
}
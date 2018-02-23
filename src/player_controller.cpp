//
// Created by Trevor Fisher on 2/20/2018.
//

#include "player_controller.h"
#include "ship.h"
#include "bullet.h"
#include "sinibomb.h"
#include "engine/input.h"
#include "world.h"

const float BULLET_FIRE_RATE = 0.12f;
const float BULLET_SPEED = 125.f;
const float PLAYER_SPEED = 12.f;

player_controller::player_controller() {
    bullet_timer = 0.f;
}
void player_controller::update(float dt) {
    minalear::controller_state *joystick = minalear::get_controller_ptr();

    if (joystick->left_stick_length > 0.15f) {
        float force_factor = PLAYER_SPEED * joystick->left_stick_length;
        owner->apply_force(joystick->left_stick * force_factor);
    }

    bullet_timer += dt;
    if (bullet_timer >= BULLET_FIRE_RATE) {
        //Fire a normal bullet
        if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::X)) {
            bullet_timer = 0.f;

            //Only happens while RUNNING the application, starting it from outside the IDE or with the Debug button works FINE?!
            glm::vec2 bullet_velocity = glm::vec2(cosf(owner->rotation), sinf(owner->rotation)) * BULLET_SPEED;
            shoot(owner->position, bullet_velocity + owner->velocity);
        }
        //Fire a SINIBOMB
        else if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::Y) && owner->mineral_count > 0) {
            bullet_timer = 0.f;
            owner->game_world->add_entity(new sinibomb(owner->position));
            owner->mineral_count--;
        }
    }
}
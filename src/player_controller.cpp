//
// Created by Trevor Fisher on 2/20/2018.
//

#include "player_controller.h"
#include "ship.h"
#include "bullet.h"
#include "sinibomb.h"
#include "engine/input.h"
#include "world.h"

float bullet_timer = 0.f;
const float BULLET_FIRE_RATE = 0.12f;
const float PLAYER_SPEED_FACTOR = 12.f;

player_controller::player_controller() {

}
void player_controller::update(float dt) {
    minalear::controller_state *joystick = minalear::get_controller_ptr();

    if (joystick->left_stick_length > 0.15f) {
        float force_factor = PLAYER_SPEED_FACTOR * joystick->left_stick_length;
        owner->apply_force(joystick->left_stick * force_factor);
        owner->rotation = atan2f(joystick->left_stick.y, joystick->left_stick.x);
    }

    bullet_timer = glm::clamp(bullet_timer - dt, 0.f, bullet_timer);
    if (bullet_timer <= 0.f) {
        //Fire a normal bullet
        if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::X)) {
            bullet_timer = BULLET_FIRE_RATE;

            glm::vec2 bullet_velocity = glm::vec2(1.f);
            bullet_velocity.x = cosf(owner->rotation);
            bullet_velocity.y = sinf(owner->rotation);

            owner->game_world->add_entity(new bullet(owner->position, (bullet_velocity * 125.f) + owner->velocity));
        }
            //Fire a SINIBOMB
        else if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::Y) && owner->mineral_count > 0) {
            bullet_timer = BULLET_FIRE_RATE;
            owner->game_world->add_entity(new sinibomb(owner->position));
            owner->mineral_count--;
        }
    }
}
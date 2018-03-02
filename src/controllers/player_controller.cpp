//
// Created by Trevor Fisher on 2/20/2018.
//

#include "player_controller.h"
#include "../entities/ship.h"
#include "../entities/sinibomb.h"
#include "../engine/input.h"
#include "../world.h"

const float BULLET_FIRE_RATE = 0.12f;
const float BULLET_SPEED = 360.f;
const float RECHARGE_DELAY = 10.f;

//Used for modifying int based shields
float shield_recharge_buffer = 0.f;

player_controller::player_controller() {
    bullet_timer = 0.f;
}
void player_controller::update(float dt) {
    minalear::controller_state *joystick = minalear::get_controller_ptr();

    //Delay timer for auto-heal
    shield_timer += dt;
    if (shield_timer >= RECHARGE_DELAY) {
        shield_recharge_buffer += 10.f * dt;

        while (shield_recharge_buffer > 1.f) {
            owner->modify_shield(1);
            shield_recharge_buffer -= 1.f;
        }
    }
    else {
        shield_recharge_buffer = 0.f;
    }

    if (joystick->left_stick_length > 0.15f) {
        float force_factor = owner->movement_speed * joystick->left_stick_length;
        owner->apply_force(joystick->left_stick * force_factor);
    }
    if (joystick->right_stick_length > 0.15f) {
        owner->rotation = atan2f(joystick->right_stick.y, joystick->right_stick.x);
    }

    if (bullet_timer >= BULLET_FIRE_RATE) {
        //Fire a normal bullet
        if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::R1)) {
            glm::vec2 bullet_velocity = glm::vec2(cosf(owner->rotation), sinf(owner->rotation)) * BULLET_SPEED;
            shoot(owner->position, bullet_velocity);
        }
        //Fire a SINIBOMB
        else if (minalear::is_button_down(minalear::JOYSTICK_BUTTONS::Y) && owner->mineral_count > 0) {
            bullet_timer = 0.f;
            owner->game_world->add_entity(new sinibomb(owner->position));
            owner->mineral_count--;
        }
    }

    ship_controller::update(dt);
}
void player_controller::on_damage(class game_entity &other, int amount) {
    shield_timer = 0.f;
}
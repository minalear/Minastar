//
// Created by Trevor Fisher on 2/25/2018.
//

#include "soldier_controller.h"
#include "campaign.h"
#include "engine/math_utils.h"

const float BULLET_FIRE_RATE = 0.2f;
const float BULLET_SPEED = 150.f;

soldier_controller::soldier_controller() {
    bullet_timer = 0.f;
    current_state = SOLDIER_STATES::Attack;

    owner->movement_speed = 14.f;

}
void soldier_controller::update(float dt) {
    //Update timers
    bullet_timer += dt;

    if (current_state == SOLDIER_STATES::Patrol) {

    }
    else if (current_state == SOLDIER_STATES::Attack) {
        //Seek out and destroy the player
        game_entity *player_entity = campaign.player_entity;
        if (!player_entity) return; //Check if player pointer is valid

        //Seek to the if they are far away, otherwise shoot them
        float dist_to_player = minalear::distance_square(owner->position, player_entity->position);
        if (dist_to_player != 0.f && dist_to_player < (250.f * 250.f)) {
            //Ensure we're slowing down
            owner->velocity = owner->velocity * 0.8f;

            //Face the player
            glm::vec2 target_real_vel = player_entity->velocity * dt;
            glm::vec2 to_player = glm::normalize((player_entity->position + target_real_vel) - owner->position);
            owner->rotation = atan2f(to_player.y, to_player.x);

            if (bullet_timer >= BULLET_FIRE_RATE) {
                bullet_timer = 0.f;
                glm::vec2 bullet_velocity = (to_player * BULLET_SPEED) + owner->velocity;
                shoot(owner->position, bullet_velocity);
            }
        }

        owner->seek(player_entity->position);
    }
    else if (current_state == SOLDIER_STATES::Defend) {

    }
}
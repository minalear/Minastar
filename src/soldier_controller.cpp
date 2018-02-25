//
// Created by Trevor Fisher on 2/25/2018.
//

#include "soldier_controller.h"
#include "campaign.h"
#include "engine/math_utils.h"

const float BULLET_FIRE_RATE = 0.2f;
const float BULLET_SPEED = 450.f;

soldier_controller::soldier_controller() {
    current_state = SOLDIER_STATES::Attack;
}
void soldier_controller::update(float dt) {
    if (current_state == SOLDIER_STATES::Patrol) {

    }
    else if (current_state == SOLDIER_STATES::Attack) {
        //Seek out and destroy the player
        game_entity *player_entity = campaign.player_entity;
        if (!player_entity) return; //Check if player pointer is valid

        //Seek to the if they are far away, otherwise shoot them
        float dist_to_player = minalear::distance(owner->position, player_entity->position);
        if (dist_to_player != 0.f && dist_to_player < 250.f) {
            //Ensure we're slowing down
            owner->velocity = owner->velocity * 0.8f;

            glm::vec2 player_position = player_entity->position;
            glm::vec2 player_velocity = player_entity->velocity;

            float time_to_target = dist_to_player / BULLET_SPEED;

            glm::vec2 target_position = player_position + (player_velocity * time_to_target);
            glm::vec2 aim_direction = glm::normalize(target_position - owner->position);

            owner->rotation = atan2f(aim_direction.y, aim_direction.x);
            if (bullet_timer >= BULLET_FIRE_RATE) {
                shoot(owner->position, aim_direction * BULLET_SPEED);
            }
        }

        owner->seek(player_entity->position);
    }
    else if (current_state == SOLDIER_STATES::Defend) {

    }

    ship_controller::update(dt);
}
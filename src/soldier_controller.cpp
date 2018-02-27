//
// Created by Trevor Fisher on 2/25/2018.
//

#include "soldier_controller.h"
#include "campaign.h"
#include "engine/math_utils.h"

const float BULLET_FIRE_RATE = 0.2f;
const float BULLET_SPEED = 450.f;

soldier_controller::soldier_controller() {
    current_state = SOLDIER_STATES::Patrol;
    wander_target = glm::vec2(0.f);
}
void soldier_controller::update(float dt) {
    if (current_state == SOLDIER_STATES::Patrol) {
        //Check if we're close to the player
        if (minalear::distance_square(owner->position, campaign.player_entity->position) < (400.f * 400.f)) {
            current_state = SOLDIER_STATES::Attack;
        }
        else {
            float wander_radius = 6.f;
            float wander_jitter = 1.f;

            wander_target += glm::vec2(minalear::rand_float(-1.f, 1.f), minalear::rand_float(-1.f, 1.f)) * wander_jitter;
            wander_target  = glm::normalize(wander_target) * wander_radius;

            owner->seek(owner->position + wander_target);
        }
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

        if (dist_to_player > 65.f) {
            owner->seek(player_entity->position);
        }
    }
    else if (current_state == SOLDIER_STATES::Defend) {
        //Seek to the help target and then begin patrolling
        if (minalear::distance_square(owner->position, help_target->position) < (200.f * 200.f)) {
            wander_target = glm::normalize(help_target->position - owner->position); //Set wander target towards help target
            current_state = SOLDIER_STATES::Patrol;
        }
        else {
            owner->seek(help_target->position);
        }
    }

    ship_controller::update(dt);
}
void soldier_controller::on_message(MESSAGE_TYPES &message, game_entity &other) {
    if (message == MESSAGE_TYPES::Help) {
        current_state = SOLDIER_STATES::Defend;
        help_target = &other;
    }
}
//
// Created by Trevor Fisher on 2/25/2018.
//

#include "soldier_controller.h"
#include "../engine/math_utils.h"
#include "../engine/audio_player.h"
#include "../campaign.h"

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

            //Wander randomly and avoid obstacles
            wander_target += glm::vec2(minalear::rand_float(-1.f, 1.f), minalear::rand_float(-1.f, 1.f)) * wander_jitter;
            wander_target  = glm::normalize(wander_target) * wander_radius;

            glm::vec2 check_pos = glm::vec2(cosf(owner->rotation), sinf(owner->rotation)) * 30.f + owner->position;
            float check_radius = 12.f;

            //Ensure the soldier stays within the map boundaries
            float dist_to_center = minalear::distance(owner->position, glm::vec2(GAME_WORLD_MAX / 2.f));
            if (dist_to_center > GAME_WORLD_MAX / 2.f) {
                float center_strength = dist_to_center / (GAME_WORLD_MAX / 2.f);
                glm::vec2 to_center = glm::normalize(glm::vec2(GAME_WORLD_MAX / 2.f) - owner->position);
                wander_target += (to_center * center_strength) * 0.5f;
            }

            //Obstacle avoidance
            glm::vec2 point;
            if (owner->game_world->check_collision(check_pos, check_radius, *owner, point)) {
                glm::vec2 vector_reflected = -glm::normalize(point - owner->position);
                float theta = atan2f(vector_reflected.y, vector_reflected.x);

                wander_target += glm::vec2(cosf(theta), sinf(theta)) * 25.f;
            }

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

                if (minalear::distance_square(owner->position, campaign.player_entity->position) < (400.f * 400.f)) {
                    minalear::audio_engine.play_sound_effect("player_shot");
                }
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
void soldier_controller::on_damage(game_entity &other, int amount) {
    //Attack the player if he attacks first and not currently in the Attack state
    if (current_state != SOLDIER_STATES::Attack && other.entity_type == ENTITY_TYPES::Player) {
        current_state = SOLDIER_STATES::Attack;
    }
}
void soldier_controller::on_death() {
    campaign.spawn_new_entity(ENTITY_TYPES::Soldier);
}
void soldier_controller::on_message(MESSAGE_TYPES &message, game_entity &other) {
    if (message == MESSAGE_TYPES::Help && current_state != SOLDIER_STATES::Attack) {
        current_state = SOLDIER_STATES::Defend;
        help_target = &other;
    }
}
//
// Created by Trevor Fisher on 3/3/2018.
//

#include "scavenger_controller.h"
#include "../engine/math_utils.h"
#include "../campaign.h"

scavenger_controller::scavenger_controller() {
    current_state = SCAVENGER_STATES::Wander;
}
void scavenger_controller::update(float dt) {
    float player_dist_sqr = minalear::distance_square(owner->position, campaign.player_entity->position);

    if (current_state == SCAVENGER_STATES::Wander) {
        if (player_dist_sqr < (600.f * 600.f)) {
            change_state(SCAVENGER_STATES::Steal);
        }
        else {
            float wander_radius = 6.f;
            float wander_jitter = 2.f;

            //Wander randomly and avoid obstacles
            wander_target += glm::vec2(minalear::rand_float(-1.f, 1.f), minalear::rand_float(-1.f, 1.f)) * wander_jitter;
            wander_target  = glm::normalize(wander_target) * wander_radius;

            glm::vec2 check_pos = glm::vec2(cosf(owner->rotation), sinf(owner->rotation)) * 30.f + owner->position;
            float check_radius = 12.f;

            //Ensure the entity stays within the map boundaries
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
    if (current_state == SCAVENGER_STATES::Steal) {
        //Attempt to steal minerals from the player
        float their_dist = -1.f;
        game_entity *mineral = owner->game_world->find_entity(ENTITY_TYPES::Mineral, campaign.player_entity->position, their_dist);

        if (mineral) {
        //Attempt to steal mineral
            owner->seek(mineral->position);
        }
        else if (player_dist_sqr > (500.f * 500.f)) {
        //Stay close to the player
            owner->seek(campaign.player_entity->position);
        }
        else if (player_dist_sqr < (480.f * 480.f)) {
        //But not too close
            glm::vec2 away_position = glm::vec2(cosf(owner->rotation), sinf(owner->rotation)) * 500.f - sqrtf(player_dist_sqr);
            owner->seek(away_position);
        }
    }
}
void scavenger_controller::on_damage(game_entity &other, int amount) { }
void scavenger_controller::on_death() {
    campaign.spawn_new_entity(ENTITY_TYPES::Scavenger);
}
void scavenger_controller::change_state(SCAVENGER_STATES state) {
    current_state = state;
}



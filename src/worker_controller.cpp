//
// Created by Trevor Fisher on 2/21/2018.
//

#include "worker_controller.h"
#include "ship.h"
#include "world.h"
#include "engine/math_utils.h"
#include "campaign.h"

const float BULLET_FIRE_RATE = 0.26f;
const float BULLET_SPEED = 128.f;

worker_controller::worker_controller() {
    current_state = WORKER_STATES::Mining;
    saved_pos = glm::vec2(0.f);
}

void worker_controller::update(float dt) {

    /* Workers will mine asteroids for minerals until they reach a threshold,
     * then they will turn green and run their cargo to Sinistar (currently 0,0)
     */

    if (current_state == WORKER_STATES::Mining) {
        float dist = -1.f;
        game_entity *closest_target = nullptr;

        //Get closest mineral (if within acceptable distance)
        //TODO: Investigate why sometimes workers won't seek out nearby minerals
        closest_target = owner->game_world->find_entity(ENTITY_TYPES::Mineral, owner->position, dist);
        if (closest_target && dist < 125.f) {
            owner->seek(closest_target->position);
            return;  //Early return to prevent seeking asteroids
        }

        //Get closest asteroid
        closest_target = owner->game_world->find_entity(ENTITY_TYPES::Asteroid, owner->position, dist);
        if (closest_target) {
            //Seek towards asteroids that are too far away, otherwise shoot them
            if (dist > closest_target->bounding_radius + 40.f) {
                owner->seek(closest_target->position);
            } else if (dist != 0.f) {
                //Ensure we're slowing down
                owner->velocity = owner->velocity * 0.8f;

                glm::vec2 asteroid_position = closest_target->position;
                glm::vec2 asteroid_velocity = closest_target->velocity;

                float time_to_target = dist / BULLET_SPEED;

                glm::vec2 target_position = asteroid_position + (asteroid_velocity * time_to_target);
                glm::vec2 aim_direction = glm::normalize(target_position - owner->position);

                owner->rotation = atan2f(aim_direction.y, aim_direction.x);

                //SHOOT HER
                if (bullet_timer >= BULLET_FIRE_RATE) {
                    shoot(owner->position, aim_direction * BULLET_SPEED);
                }
            }
        }

        //Determine if we should deliver our current payload
        if (owner->mineral_count >= 20) {
            owner->paint_color(glm::vec3(0.f, 1.f, 0.2f));
            current_state = WORKER_STATES::Deliver;
            saved_pos = owner->position;
        }
    }
    else if (current_state == WORKER_STATES::Deliver) {
        //Seek out Sinistar and deliver minerals to him
        if (!campaign.sinistar_entity) return; //Exit if we cannot find Sinistar

        float dist_to_goal = minalear::distance_square(owner->position, campaign.sinistar_entity->position);
        if (dist_to_goal <= 40.f * 40.f) {
            campaign.worker_mineral_count += owner->mineral_count;
            owner->mineral_count = 0;
            owner->paint_color(glm::vec3(1.f, 0.f, 0.f));
            current_state = WORKER_STATES::Return;
        }
        else {
            owner->seek(campaign.sinistar_entity->position);
        }
    }
    else if (current_state == WORKER_STATES::Return) {
        //Return to our old position and continue mining
        float dist_to_goal = minalear::distance_square(owner->position, saved_pos);
        if (dist_to_goal <= 40.f * 40.f) {
            current_state = WORKER_STATES::Mining;
        }
        else {
            owner->seek(saved_pos);
        }
    }

    ship_controller::update(dt);
}
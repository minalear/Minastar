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
const float WORKER_MOVE_SPEED = 12.f;

worker_controller::worker_controller() {
    bullet_timer = 0.f;
    current_state = WORKER_STATES::Mining;
    saved_pos = glm::vec2(0.f);
}

void seek(game_entity *owner, glm::vec2 target) {
    glm::vec2 target_vector = target - owner->position;
    glm::vec2 adjusted_vel = glm::normalize(target_vector) * WORKER_MOVE_SPEED;

    owner->velocity += adjusted_vel;
}
void worker_controller::update(float dt) {

    /* Workers will mine asteroids for minerals until they reach a threshold,
     * then they will turn green and run their cargo to Sinistar (currently 0,0)
     */

    //Update timers
    bullet_timer += dt;

    if (current_state == WORKER_STATES::Mining) {
        float dist = -1.f;
        game_entity *closest_target = nullptr;

        //Get closest mineral (if within acceptable distance)
        closest_target = owner->game_world->find_entity(ENTITY_TYPES::Mineral, owner->position, dist);
        if (closest_target && dist < 125.f) {
            seek(owner, closest_target->position);
            return;  //Early return to prevent seeking asteroids
        }

        //Get closest asteroid
        closest_target = owner->game_world->find_entity(ENTITY_TYPES::Asteroid, owner->position, dist);
        if (closest_target) {
            //Seek towards asteroids that are too far away, otherwise shoot them
            if (dist > closest_target->bounding_radius + 40.f) {
                seek(owner, closest_target->position);
            } else if (dist != 0.f) {
                //Ensure we're slowing down
                owner->velocity = owner->velocity * 0.8f;

                //Face the asteroid (in case it is moving)

                //TODO: Improve targeting (they don't deal with faster moving objects well)
                glm::vec2 target_real_vel = closest_target->velocity * dt;
                glm::vec2 to_asteroid = glm::normalize((closest_target->position + target_real_vel) - owner->position);
                owner->rotation = atan2f(to_asteroid.y, to_asteroid.x);

                //SHOOT HER
                if (bullet_timer >= BULLET_FIRE_RATE) {
                    bullet_timer = 0.f;
                    glm::vec2 bullet_velocity = (to_asteroid * BULLET_SPEED) + owner->velocity;
                    shoot(owner->position, bullet_velocity);
                }
            }
        }

        //Determine if we should deliver our current payload
        if (owner->mineral_count >= 40) {
            owner->paint_color(glm::vec3(0.f, 1.f, 0.2f));
            current_state = WORKER_STATES::Deliver;
            saved_pos = owner->position;
        }
    }
    else if (current_state == WORKER_STATES::Deliver) {
        //Seek out Sinistar and deliver minerals to him
        float dist_to_goal = minalear::distance_square(owner->position, glm::vec2(0.f));
        if (dist_to_goal <= 40.f * 40.f) {
            campaign.worker_mineral_count += owner->mineral_count;
            owner->mineral_count = 0;
            owner->paint_color(glm::vec3(1.f, 0.f, 0.f));
            current_state = WORKER_STATES::Return;
        }
        else {
            seek(owner, glm::vec2(0.f));
        }
    }
    else if (current_state == WORKER_STATES::Return) {
        //Return to our old position and continue mining
        float dist_to_goal = minalear::distance_square(owner->position, saved_pos);
        if (dist_to_goal <= 40.f * 40.f) {
            current_state = WORKER_STATES::Mining;
        }
        else {
            seek(owner, saved_pos);
        }
    }
}
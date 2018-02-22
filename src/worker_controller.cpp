//
// Created by Trevor Fisher on 2/21/2018.
//

#include "worker_controller.h"
#include "ship.h"
#include "world.h"
#include "bullet.h"

const float BULLET_FIRE_RATE = 0.26f;
const float BULLET_SPEED = 128.f;
const float WORKER_MOVE_SPEED = 12.f;

worker_controller::worker_controller() { }

void seek(game_entity *owner, glm::vec2 target) {
    glm::vec2 target_vector = target - owner->position;
    glm::vec2 adjusted_vel = glm::normalize(target_vector) * WORKER_MOVE_SPEED;

    owner->velocity += adjusted_vel;
}
void worker_controller::update(float dt) {

    /* Workers will attempt to pickup nearby minerals (within a distance threshold)
     * or attempt to mine asteroids for said minerals.
     */

    //Update timers
    bullet_timer = glm::clamp(bullet_timer - dt, 0.f, bullet_timer);

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
        }
        else if (dist != 0.f) {
            //Ensure we're slowing down
            owner->velocity = owner->velocity * 0.8f;

            //Face the asteroid (in case it is moving)

            //TODO: Improve targeting (they don't deal with faster moving objects well)
            glm::vec2 target_real_vel = closest_target->velocity * dt;
            glm::vec2 to_asteroid = glm::normalize((closest_target->position + target_real_vel) - owner->position);
            owner->rotation = atan2f(to_asteroid.y, to_asteroid.x);

            //SHOOT HER
            if (bullet_timer <= 0.f) {
                bullet_timer = BULLET_FIRE_RATE;
                glm::vec2 bullet_velocity = (to_asteroid * BULLET_SPEED) + owner->velocity;
                shoot(owner->position, bullet_velocity);
            }
        }

        return;  //Early return
    }
}
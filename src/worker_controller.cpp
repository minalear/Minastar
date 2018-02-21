//
// Created by Trevor Fisher on 2/21/2018.
//

#include "worker_controller.h"
#include "ship.h"
#include "world.h"

const float WORKER_MOVE_SPEED = 32.f;

worker_controller::worker_controller() { }
void worker_controller::update(float dt) {

    /* Workers will attempt to pickup nearby minerals (within a distance threshold)
     * or attempt to mine asteroids for said minerals.
     * */

    float dist = -1.f;
    game_entity *closest_mineral = owner->game_world->find_entity(ENTITY_TYPES::Mineral, owner->position, dist);

    if (closest_mineral) {
        glm::vec2 target_vector = closest_mineral->position - owner->position;
        glm::vec2 adjusted_vel = glm::normalize(target_vector) * WORKER_MOVE_SPEED;

        owner->velocity = adjusted_vel;
    }
}
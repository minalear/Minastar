//
// Created by Trevor Fisher on 2/21/2018.
//

#include "worker_controller.h"
#include "../engine/math_utils.h"
#include "../engine/audio_player.h"
#include "../entities/ship.h"
#include "../world.h"
#include "../campaign.h"

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

                    if (minalear::distance_square(owner->position, campaign.player_entity->position) < (400.f * 400.f)) {
                        minalear::audio_engine.play_sound_effect("player_shot");
                    }
                }
            }
        }

        //Determine if we should deliver our current payload
        if (owner->mineral_count >= 20) {
            change_state(WORKER_STATES::Deliver);
        }
    }
    else if (current_state == WORKER_STATES::Deliver) {
        //Seek out Sinistar and deliver minerals to him
        if (!campaign.sinistar_entity) return; //Exit if we cannot find Sinistar

        float dist_to_goal = minalear::distance_square(owner->position, campaign.sinistar_entity->position);
        if (dist_to_goal <= (40.f * 40.f)) {
            campaign.worker_mineral_count += owner->mineral_count;
            owner->mineral_count = 0;
            change_state(WORKER_STATES::Return);
        }
        else {
            owner->seek(campaign.sinistar_entity->position);
        }
    }
    else if (current_state == WORKER_STATES::Return) {
        //Return to our old position and continue mining
        float dist_to_goal = minalear::distance_square(owner->position, saved_pos);
        if (dist_to_goal <= (40.f * 40.f)) {
            change_state(WORKER_STATES::Mining);
        }
        else {
            owner->seek(saved_pos);
        }
    }
    else if (current_state == WORKER_STATES::Flee) {
        float dist_to_player = minalear::distance_square(owner->position, campaign.player_entity->position);
        if (dist_to_player >= (400.f * 400.f)) {
            //Safe distance away, just enter deliver state
            change_state(WORKER_STATES::Deliver);
        }
        else {
            //Seek away from player
            glm::vec2 vector_to_player = glm::normalize(glm::vec2(campaign.player_entity->position - owner->position));
            glm::vec2 target = (owner->position - vector_to_player);
            owner->seek(target);
        }
    }

    ship_controller::update(dt);
}
void worker_controller::on_damage(game_entity &other, int amount) {
    //Upon being attacked, send a help message to the nearest soldier and run away
    if (current_state != WORKER_STATES::Flee) {
        change_state(WORKER_STATES::Flee);

        float dist_to_soldier = 0.f;
        game_entity *closest_ally = owner->game_world->find_entity(ENTITY_TYPES::Soldier, owner->position, dist_to_soldier);
        if (!closest_ally) return; //Cannot call if they don't exist

        closest_ally->send_message(MESSAGE_TYPES::Help, *owner);
    }
}
void worker_controller::change_state(WORKER_STATES state) {
    if (state == WORKER_STATES::Deliver) {
        //Paint the ship green, save our previous state
        owner->paint_color(glm::vec3(141 / 255.f, 198 / 255.f, 63 / 255.f));
        saved_pos = owner->position;
    }
    else if (state == WORKER_STATES::Return) {
        //Paint the ship red
        owner->paint_color(glm::vec3(1.f, 0.f, 0.f));
    }
    else if (state == WORKER_STATES::Flee) {
        //Paint the ship yellow
        owner->paint_color(glm::vec3(242 / 255.f, 230 / 255.f, 100 / 255.f));
    }

    current_state = state;
}
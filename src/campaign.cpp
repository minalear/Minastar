//
// Created by Trevor Fisher on 2/22/2018.
//

#include "campaign.h"
#include "engine/audio_player.h"
#include "engine/math_utils.h"
#include "controllers/worker_controller.h"
#include "controllers/soldier_controller.h"
#include "controllers/scavenger_controller.h"

game_campaign campaign;
game_campaign::game_campaign() {
    reset();
}

void game_campaign::init(screen_manager *gui_manager, world *game_world) {
    this->gui_manager = gui_manager;
    this->game_world = game_world;

    sinistar_entity = (sinistar*)this->game_world->find_entity(ENTITY_TYPES::Sinistar);
    player_entity = (ship*)this->game_world->find_entity(ENTITY_TYPES::Player);

    //Randomly choose a corner for Sinistar to spawn in
    int corner = minalear::rand_int(0, 4);

    switch (corner) {
        case 0: sinistar_spawn = glm::vec2(0.f, 0.f); //TL
            break;
        case 1: sinistar_spawn = glm::vec2(GAME_WORLD_MAX, 0.f); //TR
            break;
        case 2: sinistar_spawn = glm::vec2(0.f, GAME_WORLD_MAX); //BL
            break;
        case 3:
       default: sinistar_spawn = glm::vec2(GAME_WORLD_MAX, GAME_WORLD_MAX); //BR
            break;
    }

    sinistar_entity->position = sinistar_spawn;
}
void game_campaign::reset() {
    worker_mineral_count = 0;
    sinistar_released = false;

    this->game_world = nullptr;
    sinistar_entity = nullptr;
    player_entity = nullptr;
    spawn_timer = 0.f;
}
void game_campaign::update(float dt) {
    //I HUNGER
    if (worker_mineral_count >= 40 && !sinistar_released) {
        sinistar_released = true;

        minalear::audio_engine.play_sound_effect("sinistar_i_live");
    }

    //Player loses
    if (player_entity->health <= 0) {
        gui_manager->switch_screen("Lose");
    }
    else if (sinistar_entity->health <= 0) {
        gui_manager->switch_screen("Victory");
    }

    //If the player approaches an unfinished Sinistar, spawn new soldiers
    spawn_timer += dt;
    if (minalear::distance_square(sinistar_entity->position, player_entity->position) < (500.f * 500.f) && spawn_timer >= 8.f) {
        spawn_new_entity(ENTITY_TYPES::Soldier);
        spawn_timer = 0.f;
    }
}

void game_campaign::spawn_new_entity(ENTITY_TYPES type) {
    glm::vec2 spawn_pos = sinistar_spawn;

    if (type == ENTITY_TYPES::Worker) {
        ship *worker = new ship(new worker_controller, type);
        worker->position = spawn_pos;
        game_world->add_entity(worker);
    }
    else if (type == ENTITY_TYPES::Soldier) {
        ship *soldier = new ship(new soldier_controller, type);
        soldier->position = spawn_pos;
        game_world->add_entity(soldier);
    }
    else if (type == ENTITY_TYPES::Scavenger) {
        ship *scavenger = new ship(new scavenger_controller, type);
        scavenger->position = spawn_pos;
        game_world->add_entity(scavenger);
    }
}
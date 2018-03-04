//
// Created by Trevor Fisher on 2/22/2018.
//

#include "campaign.h"
#include "engine/audio_player.h"

game_campaign campaign;
game_campaign::game_campaign() {
    reset();
}

void game_campaign::init(screen_manager *gui_manager, world *game_world) {
    this->gui_manager = gui_manager;
    this->game_world = game_world;

    sinistar_entity = (sinistar*)this->game_world->find_entity(ENTITY_TYPES::Sinistar);
    player_entity = (ship*)this->game_world->find_entity(ENTITY_TYPES::Player);
}
void game_campaign::reset() {
    worker_mineral_count = 0;
    sinistar_released = false;

    this->game_world = nullptr;
    sinistar_entity = nullptr;
    player_entity = nullptr;
}
void game_campaign::update() {
    //I HUNGER
    if (worker_mineral_count >= 40 && !sinistar_released) {
        sinistar_released = true;

        minalear::audio_engine.play_sound_effect("sinistar_i_live");
    }

    //Player loses
    if (player_entity->health <= 0.f) {
        gui_manager->switch_screen("Lose");
    }
}
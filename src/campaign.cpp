//
// Created by Trevor Fisher on 2/22/2018.
//

#include "campaign.h"

game_campaign campaign;
game_campaign::game_campaign() {
    worker_mineral_count = 0;
    sinistar_released = false;
}

void game_campaign::init(world *game_world) {
    this->game_world = game_world;
    sinistar_entity = (sinistar*)this->game_world->find_entity(ENTITY_TYPES::Sinistar);
    player_entity = (ship*)this->game_world->find_entity(ENTITY_TYPES::Player);
}
void game_campaign::update() {
    //I HUNGER
    if (worker_mineral_count >= 40 && !sinistar_released) {
        sinistar_released = true;
        //game_world->add_entity(new sinistar(glm::vec2(0.f)));
    }
}
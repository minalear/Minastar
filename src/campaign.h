//
// Created by Trevor Fisher on 2/22/2018.
//

#ifndef SINISTAR_CAMPAIGN_H
#define SINISTAR_CAMPAIGN_H

#include "world.h"
#include "entities/ship.h"
#include "entities/sinistar.h"
#include "GUI/screen_manager.h"

class game_campaign {
public:
    screen_manager *gui_manager;

    world *game_world;
    sinistar *sinistar_entity;
    ship *player_entity;

    bool sinistar_released;
    int worker_mineral_count;

    game_campaign();

    void init(screen_manager *gui_manager, world *game_world);
    void reset();
    void update();
};

extern game_campaign campaign;

#endif //SINISTAR_CAMPAIGN_H

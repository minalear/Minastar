//
// Created by Trevor Fisher on 2/22/2018.
//

#ifndef SINISTAR_CAMPAIGN_H
#define SINISTAR_CAMPAIGN_H

#include "world.h"

class game_campaign {
    world *game_world;

public:
    bool sinistar_released;
    int worker_mineral_count;

    game_campaign();
    void init(world *game_world);
    void update();
};

extern game_campaign campaign;

#endif //SINISTAR_CAMPAIGN_H

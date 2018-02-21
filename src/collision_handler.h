//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_COLLISION_HANDLER_H
#define SINISTAR_COLLISION_HANDLER_H

#include "game_entity.h"

bool check_collision(const game_entity &a, const game_entity &b, glm::vec2 &collision_point);

#endif //SINISTAR_COLLISION_HANDLER_H

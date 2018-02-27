//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_COLLISION_HANDLER_H
#define SINISTAR_COLLISION_HANDLER_H

#include "game_entity.h"

bool collides_with(const game_entity &a, const game_entity &b, glm::vec2 &collision_point);
bool collides_with(const game_entity &a, glm::vec2 pos, float radius, glm::vec2 &collision_point);
void resolve_collision(game_entity &a, game_entity &b, glm::vec2 &collision_point);

#endif //SINISTAR_COLLISION_HANDLER_H

//
// Created by Trevor Fisher on 2/13/2018.
//

#include "collision_handler.h"
#include "glm.hpp"

float distance_square(glm::vec2 a, glm::vec2 b) {
    return powf(b.x - a.x, 2.f) + powf(b.y - a.y, 2.f);
}

bool check_collision(const game_entity &a, const game_entity &b) {
    float dist_sqr = distance_square(a.position, b.position);
    float min_dist = powf(a.bounding_radius + b.bounding_radius, 2.f);

    return (dist_sqr < min_dist);
}
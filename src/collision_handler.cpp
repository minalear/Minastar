//
// Created by Trevor Fisher on 2/13/2018.
//

#include "collision_handler.h"
#include "engine/math_utils.h"

bool check_collision(const game_entity &a, const game_entity &b, glm::vec2 &collision_point) {
    float dist_sqr = minalear::distance_square(a.position, b.position);
    float min_dist = powf(a.bounding_radius + b.bounding_radius, 2.f);

    if (dist_sqr <= min_dist) { //Valid collision
        //Calculate the point of collision
        //The closest possible points found on both bounding circles given the angle between the two objects
        float A = b.position.x - a.position.x;
        float B = b.position.y - a.position.y;

        float theta = atan2f(B, A);

        //Position is given in reference to Object A
        collision_point.x = cosf(theta) * a.bounding_radius + a.position.x;
        collision_point.y = sinf(theta) * a.bounding_radius + a.position.y;

        return true;
    }

    return false;
}
//
// Created by Trevor Fisher on 2/13/2018.
//

#include "collision_handler.h"
#include "engine/math_utils.h"

bool collides_with(const game_entity &a, const game_entity &b, glm::vec2 &collision_point) {
    //Check collision categories
    if ((a.collides_with & b.collision_cat) == 0)
        return false;

    //Ensure neither are going to be destroyed
    if (a.do_destroy || b.do_destroy)
        return false;

    float dist_sqr = minalear::distance_square(a.position, b.position);
    float min_dist = (a.bounding_radius + b.bounding_radius) * (a.bounding_radius + b.bounding_radius);

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
bool collides_with(const game_entity &a, glm::vec2 pos, float radius, glm::vec2 &collision_point) {
    //Ensure the entity is not going to be destroyed
    if (a.do_destroy)
        return false;

    float dist_sqr = minalear::distance_square(a.position, pos);
    float min_dist = (a.bounding_radius + radius) * (a.bounding_radius + radius);

    if (dist_sqr <= min_dist) { //Valid collision
        //Calculate the point of collision
        //The closest possible points found on both bounding circles given the angle between the two objects
        float A = pos.x - a.position.x;
        float B = pos.y - a.position.y;

        float theta = atan2f(B, A);

        //Position is given in reference to Object A
        collision_point.x = cosf(theta) * a.bounding_radius + a.position.x;
        collision_point.y = sinf(theta) * a.bounding_radius + a.position.y;

        return true;
    }

    return false;
}
void resolve_collision(game_entity &a, game_entity &b, glm::vec2 &collision_point) {
    /*float dist = minalear::distance(a.position, b.position);
    float overlap = a.bounding_radius - (dist - b.bounding_radius);
    if (overlap < 0.f) overlap *= -1.f;
    overlap += 0.5f;*/

    //Push intersecting objects apart
    if (minalear::distance_square(a.position, b.position) > 0.f) {
        glm::vec2 vector = glm::normalize(a.position - b.position);

        //Nudge each object slightly
        a.position +=  vector * 0.05f;
        b.position += -vector * 0.05f;

        //Accelerate them away from one another
        a.apply_force(vector);
        b.apply_force(-vector);
    }
}
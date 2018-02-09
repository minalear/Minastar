//
// Created by Trevor Fisher on 2/8/2018.
//

#ifndef SINISTAR_GAME_ENTITY_H
#define SINISTAR_GAME_ENTITY_H

#include "glm.hpp"


class game_entity {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force_accumulator;

    float rotation;
    float bounding_radius;

    float *buffer_data;
    int vertex_count;

    game_entity();
    ~game_entity();

    void update(float dt);
    void apply_force(glm::vec2 force);
};


#endif //SINISTAR_GAME_ENTITY_H

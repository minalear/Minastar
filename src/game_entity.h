//
// Created by Trevor Fisher on 2/8/2018.
//

#ifndef SINISTAR_GAME_ENTITY_H
#define SINISTAR_GAME_ENTITY_H

#include "glm.hpp"
//#include "world.h"

enum struct ENTITY_TYPES {
    Asteroid,
    Ship,
    Bullet,
    Sinistar,
    Sinibomb
};

class game_entity {
public:
    ENTITY_TYPES entity_type;
    //TODO: What?
    class world *game_world;

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force_accumulator;

    float rotation;
    float bounding_radius;
    float friction_coefficient;

    float *buffer_data;
    int vertex_count;

    bool do_destroy;

    game_entity();
    ~game_entity();
    
    virtual void update(float dt);
    virtual void apply_force(glm::vec2 force);
    virtual void handle_collision(const game_entity &other);
};


#endif //SINISTAR_GAME_ENTITY_H

//
// Created by minalear on 2/9/2018.
//

#include "ship.h"
#include "glm.hpp"

void generate_ship_shape(ship *ship) {
    int vertex_count = 4;
    float *buffer_data = new float[vertex_count * 5];

    //Initialize all data to 1.f
    for (int i = 0; i < vertex_count * 5; i++) {
        buffer_data[i] = 1.f;
    }

    const float ship_scale = 5.f;
    buffer_data[ 0] =  1.5f * ship_scale;
    buffer_data[ 1] =  0.0f * ship_scale;

    buffer_data[ 5] = -1.5f * ship_scale;
    buffer_data[ 6] =  1.0f * ship_scale;

    buffer_data[10] = -1.2f * ship_scale;
    buffer_data[11] =  0.0f * ship_scale;

    buffer_data[15] = -1.5f * ship_scale;
    buffer_data[16] = -1.0f * ship_scale;

    ship->entity_type = ENTITY_TYPES::Ship;
    ship->vertex_count = vertex_count;
    ship->buffer_data = buffer_data;
    ship->bounding_radius = ship_scale;
    ship->position = glm::vec2(0.f, 0.f);
}

ship::ship() {
    generate_ship_shape(this);
}

void ship::update(float dt) {
    game_entity::update(dt);
}
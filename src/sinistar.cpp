//
// Created by Trevor Fisher on 2/13/2018.
//

#include "sinistar.h"
#include "glm.hpp"

void generate_sinistar_shape(sinistar *sinistar) {
    int vertex_count = 11;
    float *buffer_data = new float[vertex_count * 5];

    //Initialize all data to 1.f
    for (int i = 0; i < vertex_count * 5; i++) {
        buffer_data[i] = 1.f;
    }

    const float sinistar_scale = 5.f;
    buffer_data[ 0] =  3.0f * sinistar_scale;
    buffer_data[ 1] =  0.0f * sinistar_scale;

    buffer_data[ 5] = 10.0f * sinistar_scale;
    buffer_data[ 6] =  4.0f * sinistar_scale;

    buffer_data[10] = 15.0f * sinistar_scale;
    buffer_data[11] = 10.0f * sinistar_scale;

    buffer_data[15] = 20.0f * sinistar_scale;
    buffer_data[16] =  4.0f * sinistar_scale;

    buffer_data[20] = 27.0f * sinistar_scale;
    buffer_data[21] =  0.0f * sinistar_scale;

    buffer_data[25] = 23.5f * sinistar_scale;
    buffer_data[26] =  7.5f * sinistar_scale;

    buffer_data[30] = 20.0f * sinistar_scale;
    buffer_data[31] =  4.0f * sinistar_scale;

    buffer_data[35] = 18.5f * sinistar_scale;
    buffer_data[36] =  4.8f * sinistar_scale;

    buffer_data[40] = 11.5f * sinistar_scale;
    buffer_data[41] =  4.8f * sinistar_scale;

    buffer_data[45] = 10.0f * sinistar_scale;
    buffer_data[46] =  4.0f * sinistar_scale;

    buffer_data[50] =  6.5f * sinistar_scale;
    buffer_data[51] =  7.5f * sinistar_scale;

    sinistar->entity_type = ENTITY_TYPES::Sinistar;
    sinistar->vertex_count = vertex_count;
    sinistar->buffer_data = buffer_data;
    sinistar->bounding_radius = sinistar_scale;
    sinistar->position = glm::vec2(300.f, 125.f);
}

sinistar::sinistar() {
    generate_sinistar_shape(this);
}

void sinistar::update(float dt) {
    game_entity::update(dt);
}
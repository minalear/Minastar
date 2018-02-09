//
// Created by Trevor Fisher on 2/8/2018.
//

#include <cmath>
#include <random>
#include "asteroid.h"

const float ASTEROID_RADIUS_MIN = 12.f;
const float ASTEROID_RADIUS_MAX = 48.f;
const float ASTEROID_VARIATION_MIN = 0.9f;
const float ASTEROID_VARIATION_MAX = 1.5f;

float rand_float(float min, float max) {
    return (rand() / (float)RAND_MAX) * (max - min) + min;
}

void generate_asteroid_shape(asteroid *object) {
    int vertex_count = rand() % 10 + 8;
    float *buffer_data = new float[vertex_count * 5];

    const float asteroid_scale = rand_float(ASTEROID_RADIUS_MIN, ASTEROID_RADIUS_MAX);
    const float theta_delta = (2.f * 3.14159f) / vertex_count;
    float theta = 0.f;

    for (int i = 0; i < vertex_count; i++) {
        glm::vec2 pos = glm::vec2(cosf(theta), sinf(theta));
        float rand_scale = rand_float(ASTEROID_VARIATION_MIN, ASTEROID_VARIATION_MAX);

        //Position (XY)
        buffer_data[i * 5 + 0] = pos.x * (asteroid_scale * rand_scale);
        buffer_data[i * 5 + 1] = pos.y * (asteroid_scale * rand_scale);

        //Color (RGB)
        buffer_data[i * 5 + 2] = 167 / 255.f;
        buffer_data[i * 5 + 3] = 162 / 255.f;
        buffer_data[i * 5 + 4] = 159 / 255.f;

        theta += theta_delta;
    }

    object->vertex_count = vertex_count;
    object->buffer_data = buffer_data;
    object->bounding_radius = asteroid_scale * 2.f;
    object->position = glm::vec2(
            rand_float(asteroid_scale, 800.f - asteroid_scale),
            rand_float(asteroid_scale, 450.f - asteroid_scale));
}

asteroid::asteroid() {
    generate_asteroid_shape(this);
}
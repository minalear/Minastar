//
// Created by Trevor Fisher on 2/8/2018.
//

#include <cmath>
#include <random>
#include "asteroid.h"
#include "world.h"
#include "sinibomb.h"

const float ASTEROID_RADIUS_MIN = 12.f;
const float ASTEROID_RADIUS_MAX = 48.f;
const float ASTEROID_VARIATION_MIN = 0.87f;
const float ASTEROID_VARIATION_MAX = 1.21f;

const glm::vec3 ASTEROID_COLOR = glm::vec3(
        137 / 255.f,  //R
        129 / 255.f,  //G
        114 / 255.f); //B

float rand_float(float min, float max) {
    return (rand() / (float)RAND_MAX) * (max - min) + min;
}

void generate_asteroid_shape(asteroid *object) {
    //TODO: Look into fractal asteroid generation
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
        buffer_data[i * 5 + 2] = ASTEROID_COLOR.r;
        buffer_data[i * 5 + 3] = ASTEROID_COLOR.g;
        buffer_data[i * 5 + 4] = ASTEROID_COLOR.b;

        theta += theta_delta;
    }

    object->entity_type = ENTITY_TYPES::Asteroid;
    object->vertex_count = vertex_count;
    object->buffer_data = buffer_data;
    object->bounding_radius = asteroid_scale;
    object->position = glm::vec2(
            rand_float(asteroid_scale, 800.f - asteroid_scale),
            rand_float(asteroid_scale, 450.f - asteroid_scale));
}

asteroid::asteroid() {
    generate_asteroid_shape(this);
}

void asteroid::update(float dt) {
    rotation += 0.1f * dt;
    game_entity::update(dt);
}
void asteroid::handle_collision(const game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Bullet) {
        do_destroy = true;
        game_world->add_entity(new sinibomb(point));
    }
}
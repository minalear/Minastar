//
// Created by Trevor Fisher on 2/8/2018.
//

#include "asteroid.h"
#include "engine/math_utils.h"
#include "world.h"
#include "mineral.h"

const float ASTEROID_RADIUS_MIN = 12.f;
const float ASTEROID_RADIUS_MAX = 48.f;
const float ASTEROID_VARIATION_MIN = 0.87f;
const float ASTEROID_VARIATION_MAX = 1.21f;

const glm::vec3 ASTEROID_COLOR = glm::vec3(
        137 / 255.f,  //R
        129 / 255.f,  //G
        114 / 255.f); //B

void generate_asteroid_shape(asteroid *asteroid, float size) {
    //TODO: Look into fractal asteroid generation
    int vertex_count = minalear::rand_int(10, 18);
    float *buffer_data = new float[vertex_count * 5];

    //If a non-zero size is provided, generate a random one
    const float asteroid_scale = (size != 0.f) ? size : minalear::rand_float(ASTEROID_RADIUS_MIN, ASTEROID_RADIUS_MAX);
    const float theta_delta = (2.f * 3.14159f) / vertex_count;
    float theta = 0.f;

    for (int i = 0; i < vertex_count; i++) {
        glm::vec2 pos = glm::vec2(cosf(theta), sinf(theta));
        float rand_scale = minalear::rand_float(ASTEROID_VARIATION_MIN, ASTEROID_VARIATION_MAX);

        //Position (XY)
        buffer_data[i * 5 + 0] = pos.x * (asteroid_scale * rand_scale);
        buffer_data[i * 5 + 1] = pos.y * (asteroid_scale * rand_scale);

        //Color (RGB)
        buffer_data[i * 5 + 2] = ASTEROID_COLOR.r;
        buffer_data[i * 5 + 3] = ASTEROID_COLOR.g;
        buffer_data[i * 5 + 4] = ASTEROID_COLOR.b;

        theta += theta_delta;
    }

    asteroid->entity_type = ENTITY_TYPES::Asteroid;
    asteroid->vertex_count = vertex_count;
    asteroid->buffer_data = buffer_data;
    asteroid->bounding_radius = asteroid_scale;
    asteroid->friction_coefficient = 1.f;
    asteroid->health = (int)asteroid_scale;
}

asteroid::asteroid() {
    generate_asteroid_shape(this, 0.f);
    position = glm::vec2(
            minalear::rand_float(bounding_radius, 800.f - bounding_radius),
            minalear::rand_float(bounding_radius, 450.f - bounding_radius));
}
asteroid::asteroid(glm::vec2 pos) {
    generate_asteroid_shape(this, 0.f);
    position = pos;
}
asteroid::asteroid(float size, glm::vec2 pos) {
    generate_asteroid_shape(this, size);
    position = pos;
}

void asteroid::update(float dt) {
    rotation += 0.1f * dt;
    game_entity::update(dt);
}
void asteroid::handle_collision(const game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Bullet) {
        //Update asteroid health
        health -= 4;

        //If the asteroid is destroy, spawn two smaller ones, or destroy it completely (if too small)
        if (health <= 0) {
            do_destroy = true;
            if (bounding_radius > 10.f) {
                float asteroid_scale = bounding_radius / 2.f;
                auto left_pos  = glm::vec2(minalear::rand_float(position.x - asteroid_scale, position.x + asteroid_scale),
                                           minalear::rand_float(position.y - asteroid_scale, position.y + asteroid_scale));
                auto right_pos = glm::vec2(minalear::rand_float(position.x - asteroid_scale, position.x + asteroid_scale),
                                           minalear::rand_float(position.y - asteroid_scale, position.y + asteroid_scale));

                asteroid *left_asteroid  = new asteroid(asteroid_scale, left_pos);
                asteroid *right_asteroid = new asteroid(asteroid_scale, right_pos);

                float vel_factor = minalear::rand_float(1.f, 1.2f);
                left_asteroid->velocity = (left_pos - right_pos) * vel_factor;
                right_asteroid->velocity = (right_pos - left_pos) * vel_factor;

                game_world->add_entity(left_asteroid);
                game_world->add_entity(right_asteroid);
            }
        }

        //one-in-ten chance of spawning
        if (minalear::rand_float(0.f, 100.f) < 10.f) {
            glm::vec2 mineral_vel = -other.velocity;
            mineral_vel = glm::normalize(mineral_vel) * 10.f;
            game_world->add_entity(new mineral(point, mineral_vel));
        }
    }
}
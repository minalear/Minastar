//
// Created by Trevor Fisher on 2/8/2018.
//

#include "asteroid.h"
#include "engine/math_utils.h"
#include "world.h"
#include "mineral.h"

const float ASTEROID_RADIUS_MIN = 12.f;
const float ASTEROID_RADIUS_MAX = 52.f;
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
    asteroid->friction_coefficient = 0.999f;
    asteroid->health = (int)asteroid_scale;

    asteroid->set_collision_category(COLLISION_CATEGORIES::Asteroid);
    asteroid->add_collision_type(COLLISION_CATEGORIES::Player);
    asteroid->add_collision_type(COLLISION_CATEGORIES::Ally_Bullet);
    asteroid->add_collision_type(COLLISION_CATEGORIES::Enemy);
    asteroid->add_collision_type(COLLISION_CATEGORIES::Enemy_Bullet);
    asteroid->add_collision_type(COLLISION_CATEGORIES::Asteroid); //Asteroids will push other asteroids
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

        //TODO: Balance mineral spawn amounts
        //Asteroids will spawn various sized chunks
        if (health <= 0) {
            do_destroy = true;
            if (bounding_radius > 10.f) {
                float total_mass = bounding_radius * 2.f;
                while (total_mass >= 0.f) {
                    float chunk_mass = minalear::rand_float(5.f, total_mass / 1.5f);
                    total_mass -= chunk_mass;

                    float chunk_radius = chunk_mass / 2.f;
                    auto chunk_position = glm::vec2(minalear::rand_float(position.x - chunk_radius, position.x + chunk_mass),
                                                    minalear::rand_float(position.y - chunk_radius, position.y + chunk_radius));
                    auto to_asteroid_center = glm::normalize(chunk_position - position);

                    //Spawn minerals for small chunks, and spawn asteroids for larger ones
                    if (chunk_mass < 10.f) {
                        mineral *entity_mineral = new mineral(chunk_position, to_asteroid_center * 12.f);
                        game_world->add_entity(entity_mineral);
                    }
                    else {
                        asteroid *entity_asteroid = new asteroid(chunk_radius, chunk_position);
                        game_world->add_entity(entity_asteroid);
                    }
                }
            }
        }

        //Rare chance of spawning a mineral on shot
        if (minalear::rand_float(0.f, 100.f) < 4.f) {
            glm::vec2 mineral_vel = -other.velocity;
            mineral_vel = glm::normalize(mineral_vel) * 10.f;

            mineral *entity_mineral = new mineral(point, mineral_vel);
            game_world->add_entity(entity_mineral);
        }
    }
}
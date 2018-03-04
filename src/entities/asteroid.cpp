//
// Created by Trevor Fisher on 2/8/2018.
//

#include "../entities/asteroid.h"
#include "../engine/math_utils.h"
#include "../engine/audio_player.h"
#include "../world.h"
#include "../campaign.h"
#include "mineral.h"

const float ASTEROID_RADIUS_MIN = 14.f;
const float ASTEROID_RADIUS_MAX = 72.f;
const float ASTEROID_ROUGHNESS = 0.51f;

const glm::vec3 ASTEROID_COLOR = glm::vec3(
        137 / 255.f,  //R
        129 / 255.f,  //G
        114 / 255.f   //B
);

void gen_random_shape(float *depth_data, int left_index, int right_index, float displacement) {
    if ((left_index + 1) == right_index) return;
    int mid_index = (left_index + right_index) / 2;

    float depth = (depth_data[left_index] + depth_data[right_index]) / 2.f;
    depth      += minalear::rand_float(-1.f, 1.f) * displacement;

    depth_data[mid_index] = glm::clamp(depth, 0.8f, 1.2f);

    displacement *= ASTEROID_ROUGHNESS;
    gen_random_shape(depth_data, left_index, mid_index, displacement);
    gen_random_shape(depth_data, mid_index, right_index, displacement);
}
void generate_asteroid_shape(asteroid *asteroid, float size) {
    int vertex_count = 72;

    //Temporary buffer for storing depth information, initialize all points to 1
    float *depth_data = new float[vertex_count];
    for (int i = 0; i < vertex_count; i++) {
        depth_data[i] = 1.f;
    }

    //Generate a random fractal shape
    gen_random_shape(depth_data, 0, vertex_count - 1, 1.f);

    //Find the average depth
    float min_depth = 2.f;
    float max_depth = 0.f;
    for (int i = 0; i < vertex_count; i++) {
        if (depth_data[i] < min_depth) min_depth = depth_data[i];
        if (depth_data[i] > max_depth) max_depth = depth_data[i];
    }
    float avg_depth = (min_depth + max_depth) / 2.f;

    //Create asteroid data buffer
    float *buffer_data = new float[vertex_count * 5];

    //If a non-zero size is provided, generate a random one
    const float asteroid_scale = ((size != 0.f) ? size : minalear::rand_float(ASTEROID_RADIUS_MIN, ASTEROID_RADIUS_MAX)) * avg_depth;
    const float theta_delta = (2.f * 3.14159f) / vertex_count;
    float theta = 0.f;

    for (int i = 0; i < vertex_count; i++) {
        glm::vec2 pos = glm::vec2(cosf(theta), sinf(theta));
        float depth = depth_data[i];

        //Position (XY)
        buffer_data[i * 5 + 0] = pos.x * (asteroid_scale * depth);
        buffer_data[i * 5 + 1] = pos.y * (asteroid_scale * depth);

        //Color (RGB)
        buffer_data[i * 5 + 2] = ASTEROID_COLOR.r;
        buffer_data[i * 5 + 3] = ASTEROID_COLOR.g;
        buffer_data[i * 5 + 4] = ASTEROID_COLOR.b;

        theta += theta_delta;
    }

    //Cleanup unused buffer
    delete[] depth_data;

    asteroid->entity_type = ENTITY_TYPES::Asteroid;
    asteroid->vertex_count = vertex_count;
    asteroid->buffer_data = buffer_data;
    asteroid->bounding_radius = asteroid_scale;
    asteroid->friction_coefficient = 0.999f;
    asteroid->set_health((int)asteroid_scale);

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
void asteroid::handle_collision(game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Bullet) {
        //Rare chance of spawning a mineral on shot
        if (minalear::rand_float(0.f, 100.f) < 4.f) {
            glm::vec2 mineral_vel = -other.velocity;
            mineral_vel = glm::normalize(mineral_vel) * 10.f;

            mineral *entity_mineral = new mineral(point, mineral_vel);
            game_world->add_entity(entity_mineral);
        }
    }
}
void asteroid::damage(game_entity &other, int damage) {
    game_entity::damage(other, damage);

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
                auto chunk_position = glm::vec2(minalear::rand_float(position.x - chunk_radius, position.x + chunk_radius),
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

        if (minalear::distance_square(position, campaign.player_entity->position) < (400.f * 400.f)) {
            minalear::audio_engine.play_sound_effect("explosion");
        }
    }
}
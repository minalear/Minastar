//
// Created by minalear on 2/13/2018.
//

#include "bullet.h"
#include "glm.hpp"

void generate_bullet_shape(bullet *bullet) {
    int vertex_count = 4;
    float *buffer_data = new float[vertex_count * 5];

    const float bullet_scale = 3.f;
    const float theta_delta = (2.f * 3.14159f) / vertex_count;
    float theta = 0.f;

    for (int i = 0; i < vertex_count; i++) {
        glm::vec2 pos = glm::vec2(cosf(theta), sinf(theta));

        //Position (XY)
        buffer_data[i * 5 + 0] = pos.x * bullet_scale;
        buffer_data[i * 5 + 1] = pos.y * bullet_scale;

        //Color (RGB)
        buffer_data[i * 5 + 2] = 167 / 255.f;
        buffer_data[i * 5 + 3] = 162 / 255.f;
        buffer_data[i * 5 + 4] = 159 / 255.f;

        theta += theta_delta;
    }

    bullet->entity_type = ENTITY_TYPES::Bullet;
    bullet->vertex_count = vertex_count;
    bullet->buffer_data = buffer_data;
    bullet->bounding_radius = bullet_scale;
}

bullet::bullet(glm::vec2 pos, glm::vec2 vel) {
    generate_bullet_shape(this);
    this->position = pos;
    this->velocity = vel;
    this->friction_coefficient = 1.f;
};
void bullet::update(float dt) {
    game_entity::update(dt);
}
void bullet::handle_collision(const game_entity &other) {
    if (other.entity_type == ENTITY_TYPES::Asteroid) {
        do_destroy = true;
    }
}
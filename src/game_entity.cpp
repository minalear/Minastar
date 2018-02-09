//
// Created by Trevor Fisher on 2/8/2018.
//

#include "game_entity.h"

game_entity::game_entity() {
    rotation = 0.f;
    bounding_radius = 0.f;
    vertex_count = 0;
}
game_entity::~game_entity() {
    if (this->buffer_data) {
        delete[] this->buffer_data;
    }
}

void game_entity::update(float dt) {
    this->position += this->velocity * dt;
    this->velocity *= 0.9f; //Apply subtle friction
    this->velocity += force_accumulator;

    this->force_accumulator = glm::vec2(0.f);
}
void game_entity::apply_force(glm::vec2 force) {
    this->force_accumulator += force;
}
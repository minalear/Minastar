//
// Created by Trevor Fisher on 2/8/2018.
//

#include "game_entity.h"
#include "world.h"

int game_entity::next_valid_entity_id = 0;

game_entity::game_entity() {
    unique_id = next_valid_entity_id++;

    collision_cat = 0x0;
    collides_with = 0x0;

    rotation = 0.f;
    bounding_radius = 0.f;
    vertex_count = 0;
    do_destroy = false;
    friction_coefficient = 0.9f;
    movement_speed = 12.f;
}
game_entity::~game_entity() {
    if (this->buffer_data) {
        delete[] this->buffer_data;
    }
}

void game_entity::update(float dt) {
    this->position += this->velocity * dt;
    this->velocity *= friction_coefficient; //Apply subtle friction
    this->velocity += force_accumulator;

    this->force_accumulator = glm::vec2(0.f);
}
void game_entity::apply_force(glm::vec2 force) {
    this->force_accumulator += force;
}
void game_entity::handle_collision(const game_entity &other, glm::vec2 point) { }
void game_entity::paint_color(glm::vec3 color) {
    for (int i = 0; i < vertex_count; i++) {
        buffer_data[i * 5 + 2] = color.r;
        buffer_data[i * 5 + 3] = color.g;
        buffer_data[i * 5 + 4] = color.b;
    }

    game_world->mark_world_for_update();
}

void game_entity::set_collision_category(COLLISION_CATEGORIES category) {
    collision_cat = (COLLISION_CATEGORIES::All & category);
}
void game_entity::add_collision_type(COLLISION_CATEGORIES category) {
    collides_with |= (COLLISION_CATEGORIES::All & category);
}
void game_entity::seek(glm::vec2 target) {
    glm::vec2 target_vector = target - position;
    glm::vec2 adjusted_vel = glm::normalize(target_vector) * movement_speed;

    velocity += adjusted_vel;
}
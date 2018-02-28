//
// Created by Trevor Fisher on 2/20/2018.
//

#include "mineral.h"

void generate_mineral_shape(mineral *mineral) {
    int vertex_count = 6;
    float *mineral_data = new float[vertex_count * 5];

    const float mineral_scale = 2.3f;
    const float theta_delta = (2.f * 3.14159f) / vertex_count;
    float theta = 0.f;

    for (int i = 0; i < vertex_count; i++) {
        glm::vec2 pos = glm::vec2(cosf(theta), sinf(theta));

        //Position (XY)
        mineral_data[i * 5 + 0] = pos.x * mineral_scale;
        mineral_data[i * 5 + 1] = pos.y * mineral_scale;

        //Color (RGB)
        mineral_data[i * 5 + 2] = 141 / 255.f;
        mineral_data[i * 5 + 3] = 198 / 255.f;
        mineral_data[i * 5 + 4] =  63 / 255.f;

        theta += theta_delta;
    }

    mineral->entity_type = ENTITY_TYPES::Mineral;
    mineral->vertex_count = vertex_count;
    mineral->buffer_data = mineral_data;
    mineral->bounding_radius = mineral_scale;
}

mineral::mineral(glm::vec2 pos, glm::vec2 vel){
    generate_mineral_shape(this);
    this->position = pos;
    this->velocity = vel;
    this->friction_coefficient = 0.95f;

    this->set_collision_category(COLLISION_CATEGORIES::Mineral);
    this->add_collision_type(COLLISION_CATEGORIES::Player);
    this->add_collision_type(COLLISION_CATEGORIES::Enemy);
}
void mineral::update(float dt) {
    game_entity::update(dt);
}
void mineral::handle_collision(game_entity &other, glm::vec2 point) {
    do_destroy = true;
}
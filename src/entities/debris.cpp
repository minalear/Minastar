//
// Created by Trevor Fisher on 3/3/2018.
//

#include "debris.h"
#include "../engine/math_utils.h"

void generate_debris_shape(debris *debris) {
    int vertex_count = 6;
    float *buffer_data = new float[vertex_count * 5];

    const float entity_scale = minalear::rand_float(2.5f, 8.f);
    const float theta_delta = (2.f * 3.14159f) / vertex_count;
    float theta = 0.f;

    glm::vec3 rand_color = glm::vec3(
            minalear::rand_float(159 / 255.f, 1.f),
            minalear::rand_float(0.1f, 67 / 255.f),
            minalear::rand_float(0.1f, 67 / 255.f));

    for (int i = 0; i < vertex_count; i++) {
        glm::vec2 pos = glm::vec2(cosf(theta), sinf(theta));
        float rand_depth = minalear::rand_float(1.f, entity_scale);

        //Position (XY)
        buffer_data[i * 5 + 0] = pos.x * rand_depth;
        buffer_data[i * 5 + 1] = pos.y * rand_depth;

        //Color (RGB)
        buffer_data[i * 5 + 2] = rand_color.r;
        buffer_data[i * 5 + 3] = rand_color.g;
        buffer_data[i * 5 + 4] = rand_color.b;

        theta += theta_delta;
    }

    debris->entity_type = ENTITY_TYPES::Debris;
    debris->vertex_count = vertex_count;
    debris->buffer_data = buffer_data;
    debris->bounding_radius = entity_scale;
}

debris::debris(glm::vec2 pos, glm::vec2 center, glm::vec2 vel){
    generate_debris_shape(this);
    this->position = pos;
    this->velocity = glm::normalize(pos - center) * 6.f + vel;
    this->friction_coefficient = 1.f;

    //Random to randomize despawn
    life_timer = minalear::rand_float(-4.f, 0.f);

    //They don't interact with anything
    this->set_collision_category(COLLISION_CATEGORIES::None);
    this->add_collision_type(COLLISION_CATEGORIES::None);
}
void debris::update(float dt) {
    rotation += 0.2f * dt;
    game_entity::update(dt);

    life_timer += dt;
    if (life_timer > 5.f) {
        do_destroy = true;
    }
}
void debris::handle_collision(game_entity &other, glm::vec2 point) { }
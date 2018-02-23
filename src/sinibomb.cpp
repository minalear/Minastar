//
// Created by Trevor Fisher on 2/15/2018.
//

#include "sinibomb.h"
#include "world.h"

game_entity *sinistar_ptr;

void generate_sinibomb_shape(sinibomb *bomb) {
    int vertex_count = 4;
    float *bomb_data = new float[vertex_count * 5];

    const float bomb_scale = 2.3f;
    const float theta_delta = (2.f * 3.14159f) / vertex_count;
    float theta = 0.f;

    for (int i = 0; i < vertex_count; i++) {
        glm::vec2 pos = glm::vec2(cosf(theta), sinf(theta));

        //Position (XY)
        bomb_data[i * 5 + 0] = pos.x * bomb_scale;
        bomb_data[i * 5 + 1] = pos.y * bomb_scale;

        //Color (RGB)
        bomb_data[i * 5 + 2] =  60 / 255.f;
        bomb_data[i * 5 + 3] = 184 / 255.f;
        bomb_data[i * 5 + 4] = 120 / 255.f;

        theta += theta_delta;
    }

    bomb->entity_type = ENTITY_TYPES::Sinibomb;
    bomb->vertex_count = vertex_count;
    bomb->buffer_data = bomb_data;
    bomb->bounding_radius = bomb_scale;
}

sinibomb::sinibomb(glm::vec2 pos){
    generate_sinibomb_shape(this);
    this->position = pos;
    this->friction_coefficient = 1.f; //No friction

    this->set_collision_category(COLLISION_CATEGORIES::Ally_Bullet);
    this->add_collision_type(COLLISION_CATEGORIES::Enemy);
}
void sinibomb::update(float dt) {
    //Get pointer to Sinistar if we don't have one
    if (!sinistar_ptr) {
        sinistar_ptr = game_world->find_entity(ENTITY_TYPES::Sinistar);
    }

    //Track towards Sinistar, but only if he's present on the game world
    if (sinistar_ptr) {
        glm::vec2 target_position = sinistar_ptr->position + (sinistar_ptr->velocity * dt);
        glm::vec2 move_vector = glm::normalize(target_position - position);

        const float BOMB_SPEED = 200.f;
        velocity = move_vector * BOMB_SPEED;
    }
    game_entity::update(dt);
}
void sinibomb::handle_collision(const game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Sinistar) {
        do_destroy = true;
    }
}
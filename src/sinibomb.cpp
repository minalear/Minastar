//
// Created by Trevor Fisher on 2/15/2018.
//

#include "sinibomb.h"
#include "campaign.h"

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
    this->movement_speed = 50.f;

    this->set_collision_category(COLLISION_CATEGORIES::Ally_Bullet);
    this->add_collision_type(COLLISION_CATEGORIES::Enemy);
    this->add_collision_type(COLLISION_CATEGORIES::Asteroid);
}
void sinibomb::update(float dt) {
    //Track towards Sinistar, but only if he's present on the game world
    if (campaign.sinistar_entity) {
        glm::vec2 target_position = campaign.sinistar_entity->position + (campaign.sinistar_entity->velocity * dt);
        seek(target_position);
    }
    game_entity::update(dt);
}
void sinibomb::handle_collision(game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Sinistar) {
        other.damage(*this, 1); //Deals 1 to Sinistar
    }
    else if (other.entity_type == ENTITY_TYPES::Worker || other.entity_type == ENTITY_TYPES::Soldier) {
        other.damage(*this, other.health); //Destroy enemy ships
    }
    else if (other.entity_type == ENTITY_TYPES::Asteroid) {
        other.damage(*this, other.health); //Destroy asteroids
    }

    do_destroy = true;
}
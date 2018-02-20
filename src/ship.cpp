//
// Created by minalear on 2/9/2018.
//

#include "ship.h"
#include "ship_controller.h"

void generate_player_ship(ship *ship) {
    int vertex_count = 4;
    float *buffer_data = new float[vertex_count * 5];

    //Initialize all data to 1.f
    for (int i = 0; i < vertex_count * 5; i++) {
        buffer_data[i] = 1.f;
    }

    const float ship_scale = 5.f;
    buffer_data[ 0] =  1.5f * ship_scale;
    buffer_data[ 1] =  0.0f * ship_scale;

    buffer_data[ 5] = -1.5f * ship_scale;
    buffer_data[ 6] =  1.0f * ship_scale;

    buffer_data[10] = -1.2f * ship_scale;
    buffer_data[11] =  0.0f * ship_scale;

    buffer_data[15] = -1.5f * ship_scale;
    buffer_data[16] = -1.0f * ship_scale;

    ship->entity_type = ENTITY_TYPES::Player;
    ship->vertex_count = vertex_count;
    ship->buffer_data = buffer_data;
    ship->bounding_radius = ship_scale;
    ship->position = glm::vec2(0.f, 0.f);
}
void generate_worker_ship(ship *ship) {
    int vertex_count = 15;
    float *buffer_data = new float[vertex_count * 5];

    //Initialize position data to 0.f and color data to 1,0,0 (red)
    for (int i = 0; i < vertex_count; i++) {
        buffer_data[i * 5 + 0] = 0.f;
        buffer_data[i * 5 + 1] = 0.f;

        buffer_data[i * 5 + 2] = 1.f;
        buffer_data[i * 5 + 3] = 0.f;
        buffer_data[i * 5 + 4] = 0.f;
    }

    const float ship_scale = 4.f;
    buffer_data[ 0] =  0.0f * ship_scale;
    buffer_data[ 1] =  0.0f * ship_scale;

    buffer_data[ 5] = -1.0f * ship_scale;
    buffer_data[ 6] = -1.0f * ship_scale;

    buffer_data[10] =  0.0f * ship_scale;
    buffer_data[11] = -2.0f * ship_scale;

    buffer_data[15] =  1.0f * ship_scale;
    buffer_data[16] = -2.0f * ship_scale;

    buffer_data[20] =  2.0f * ship_scale;
    buffer_data[21] = -1.0f * ship_scale;

    buffer_data[25] =  2.0f * ship_scale;
    buffer_data[26] = -3.0f * ship_scale;

    buffer_data[30] =  0.0f * ship_scale;
    buffer_data[31] = -3.0f * ship_scale;

    buffer_data[35] = -2.0f * ship_scale;
    buffer_data[36] = -1.0f * ship_scale;

    buffer_data[40] = -2.0f * ship_scale;
    buffer_data[41] =  1.0f * ship_scale;

    buffer_data[45] =  0.0f * ship_scale;
    buffer_data[46] =  3.0f * ship_scale;

    buffer_data[50] =  2.0f * ship_scale;
    buffer_data[51] =  3.0f * ship_scale;

    buffer_data[55] =  2.0f * ship_scale;
    buffer_data[56] =  1.0f * ship_scale;

    buffer_data[60] =  1.0f * ship_scale;
    buffer_data[61] =  2.0f * ship_scale;

    buffer_data[65] =  0.0f * ship_scale;
    buffer_data[66] =  2.0f * ship_scale;

    buffer_data[70] = -1.0f * ship_scale;
    buffer_data[71] =  1.0f * ship_scale;

    ship->entity_type = ENTITY_TYPES::Player;
    ship->vertex_count = vertex_count;
    ship->buffer_data = buffer_data;
    ship->bounding_radius = 2.5f * ship_scale;
    ship->position = glm::vec2(0.f, 0.f);
}

ship::ship(ship_controller* controller, ENTITY_TYPES ship_type) {
    mineral_count = 0;
    this->controller = controller;
    this->controller->owner = this;

    if (ship_type == ENTITY_TYPES::Player) {
        generate_player_ship(this);
    }
    else {
        generate_worker_ship(this);
    }
}

void ship::update(float dt) {
    controller->update(dt);
    game_entity::update(dt);
}
void ship::handle_collision(const game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Mineral) {
        mineral_count++;
    }
}
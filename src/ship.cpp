//
// Created by minalear on 2/9/2018.
//

#include "ship.h"
#include "ship_controller.h"
#include "campaign.h"
#include "mineral.h"
#include "engine/math_utils.h"

const float PLAYER_MOVE_SPEED  = 12.f;
const float WORKER_MOVE_SPEED  = 12.f;
const float SOLDIER_MOVE_SPEED = 15.f;

const int PLAYER_HEALTH = 80;
const int WORKER_HEALTH = 10;
const int SOLDIER_HEALTH = 15;

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

    ship->vertex_count = vertex_count;
    ship->buffer_data = buffer_data;
    ship->bounding_radius = ship_scale;
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

    ship->vertex_count = vertex_count;
    ship->buffer_data = buffer_data;
    ship->bounding_radius = 2.5f * ship_scale;
}
void generate_soldier_ship(ship *ship) {
    int vertex_count = 8;
    float *buffer_data = new float[vertex_count * 5];

    //Initialize position data to 0.f and color data to 1,0,0 (red)
    for (int i = 0; i < vertex_count; i++) {
        buffer_data[i * 5 + 0] = 0.f;
        buffer_data[i * 5 + 1] = 0.f;

        buffer_data[i * 5 + 2] = 1.f;
        buffer_data[i * 5 + 3] = 0.f;
        buffer_data[i * 5 + 4] = 0.f;
    }

    const float ship_scale = 5.f;
    buffer_data[ 0] =  1.5f * ship_scale;
    buffer_data[ 1] =  0.0f * ship_scale;

    buffer_data[ 5] =  0.5f * ship_scale;
    buffer_data[ 6] =  1.0f * ship_scale;

    buffer_data[10] =  1.5f * ship_scale;
    buffer_data[11] =  3.0f * ship_scale;

    buffer_data[15] = -1.5f * ship_scale;
    buffer_data[16] =  1.0f * ship_scale;

    buffer_data[20] = -0.5f * ship_scale;
    buffer_data[21] =  0.0f * ship_scale;

    buffer_data[25] = -1.5f * ship_scale;
    buffer_data[26] = -1.0f * ship_scale;

    buffer_data[30] =  1.5f * ship_scale;
    buffer_data[31] = -3.0f * ship_scale;

    buffer_data[35] =  0.5f * ship_scale;
    buffer_data[36] = -1.0f * ship_scale;

    ship->vertex_count = vertex_count;
    ship->buffer_data = buffer_data;
    ship->bounding_radius = 2.25f * ship_scale;
}

ship::ship(ship_controller* controller, ENTITY_TYPES ship_type) {
    mineral_count = 0;
    this->controller = controller;
    this->controller->owner = this;
    entity_type = ship_type;
    position = glm::vec2(0.f);

    //Setup type specific parameters
    if (ship_type == ENTITY_TYPES::Player) {
        generate_player_ship(this);
        movement_speed = PLAYER_MOVE_SPEED;
        set_health(PLAYER_HEALTH);

        set_collision_category(COLLISION_CATEGORIES::Player);
        add_collision_type(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Enemy_Bullet);
        add_collision_type(COLLISION_CATEGORIES::Asteroid);
        add_collision_type(COLLISION_CATEGORIES::Mineral);
    }
    else if (ship_type == ENTITY_TYPES::Worker) {
        generate_worker_ship(this);
        movement_speed = WORKER_MOVE_SPEED;
        set_health(WORKER_HEALTH);

        set_collision_category(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Player);
        add_collision_type(COLLISION_CATEGORIES::Ally_Bullet);
        add_collision_type(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Asteroid);
        add_collision_type(COLLISION_CATEGORIES::Mineral);
    }
    else {
        generate_soldier_ship(this);
        movement_speed = SOLDIER_MOVE_SPEED;
        set_health(SOLDIER_HEALTH);

        set_collision_category(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Player);
        add_collision_type(COLLISION_CATEGORIES::Ally_Bullet);
        add_collision_type(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Asteroid);
        add_collision_type(COLLISION_CATEGORIES::Mineral);
    }
}

void ship::update(float dt) {
    rotation = atan2f(velocity.y, velocity.x);

    controller->update(dt);
    game_entity::update(dt);
}
void ship::handle_collision(game_entity &other, glm::vec2 point) {
    if (other.entity_type == ENTITY_TYPES::Mineral) {
        mineral_count++;
    }
}
void ship::damage(game_entity &other, int amount) {
    if (controller) {
        controller->on_damage(other, amount);
    }

    game_entity::damage(other, amount);

    //Drop all minerals on death
    if (health <= 0.f) {
        for (int i = 0; i < mineral_count; i++) {
            glm::vec2 mineral_position = glm::vec2(
                    minalear::rand_float(position.x - bounding_radius, position.x + bounding_radius),
                    minalear::rand_float(position.y - bounding_radius, position.y + bounding_radius));
            game_world->add_entity(new mineral(mineral_position, velocity));
        }
    }
}
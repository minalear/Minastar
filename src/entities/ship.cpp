//
// Created by minalear on 2/9/2018.
//

#include "ship.h"
#include "../engine/math_utils.h"
#include "../engine/audio_player.h"
#include "../controllers/ship_controller.h"
#include "../campaign.h"
#include "mineral.h"
#include "debris.h"

const float PLAYER_MOVE_SPEED  = 18.f;
const float WORKER_MOVE_SPEED  = 12.f;
const float SOLDIER_MOVE_SPEED = 15.f;
const float SCAVENGER_MOVE_SPEED = 38.f;

const int PLAYER_HEALTH = 40;
const int PLAYER_SHIELD = 20;
const float PLAYER_BOOST = 35.f;

const int WORKER_HEALTH = 12;
const int SOLDIER_HEALTH = 15;
const int SCAVENGER_HEALTH = 10;

//TODO: Instance these models, rather than generate them each time
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
void generate_scavenger_ship(ship *ship) {
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

    const float ship_scale = 6.f;
    buffer_data[ 0] =  2.0f * ship_scale;
    buffer_data[ 1] =  0.0f * ship_scale;

    buffer_data[ 5] =  0.0f * ship_scale;
    buffer_data[ 6] = -0.5f * ship_scale;

    buffer_data[10] = -1.0f * ship_scale;
    buffer_data[11] = -1.5f * ship_scale;

    buffer_data[15] = -2.0f * ship_scale;
    buffer_data[16] = -0.5f * ship_scale;

    buffer_data[20] = -1.0f * ship_scale;
    buffer_data[21] =  0.0f * ship_scale;

    buffer_data[25] = -2.0f * ship_scale;
    buffer_data[26] =  0.5f * ship_scale;

    buffer_data[30] = -1.0f * ship_scale;
    buffer_data[31] =  1.5f * ship_scale;

    buffer_data[35] =  0.0f * ship_scale;
    buffer_data[36] =  0.5f * ship_scale;

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
        set_shield(PLAYER_SHIELD);
        set_boost(PLAYER_BOOST);

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
        set_shield(0);
        set_boost(0.f);

        set_collision_category(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Player);
        add_collision_type(COLLISION_CATEGORIES::Ally_Bullet);
        add_collision_type(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Asteroid);
        add_collision_type(COLLISION_CATEGORIES::Mineral);
    }
    else if (ship_type == ENTITY_TYPES::Soldier) {
        generate_soldier_ship(this);
        movement_speed = SOLDIER_MOVE_SPEED;
        set_health(SOLDIER_HEALTH);
        set_shield(0);
        set_boost(0.f);

        set_collision_category(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Player);
        add_collision_type(COLLISION_CATEGORIES::Ally_Bullet);
        add_collision_type(COLLISION_CATEGORIES::Enemy);
        add_collision_type(COLLISION_CATEGORIES::Asteroid);
        //add_collision_type(COLLISION_CATEGORIES::Mineral);
    }
    else if (ship_type == ENTITY_TYPES::Scavenger) {
        generate_scavenger_ship(this);
        movement_speed = SCAVENGER_MOVE_SPEED;
        set_health(SCAVENGER_HEALTH);
        set_shield(0);
        set_boost(0.f);

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

        if (entity_type == ENTITY_TYPES::Player) {
            minalear::audio_engine.play_sound_effect("pickup");
        }
    }
}
void ship::damage(game_entity &other, int amount) {
    if (controller) {
        controller->on_damage(other, amount);
    }

    //Damage carries through shields when it exceeds it (works at 0)
    if (amount > shield) {
        game_entity::damage(other, amount - shield);
        shield = 0;
    }
    else {
        modify_shield(-amount);
    }

    //Drop all minerals on death and spawn some debris
    if (health <= 0.f) {
        for (int i = 0; i < mineral_count; i++) {
            glm::vec2 mineral_position = glm::vec2(
                    minalear::rand_float(position.x - bounding_radius, position.x + bounding_radius),
                    minalear::rand_float(position.y - bounding_radius, position.y + bounding_radius));
            game_world->add_entity(new mineral(mineral_position, velocity));
        }
        for (int i = 0; i < 8; i++) {
            glm::vec2 debris_position = glm::vec2(
                    minalear::rand_float(position.x - bounding_radius, position.x + bounding_radius),
                    minalear::rand_float(position.y - bounding_radius, position.y + bounding_radius));
            game_world->add_entity(new debris(debris_position, position, velocity));

            if (minalear::distance_square(position, campaign.player_entity->position) < (400.f * 400.f)) {
                minalear::audio_engine.play_sound_effect("explosion");
            }
        }
    }
}
void ship::send_message(MESSAGE_TYPES message, game_entity &sender) {
    controller->on_message(message, sender);
}

void ship::set_shield(int amount) {
    shield = amount;
    max_shield = amount;
}
void ship::modify_shield(int amount) {
    shield = glm::clamp(shield + amount, 0, max_shield);
}
void ship::set_boost(float amount) {
    boost = amount;
    max_boost = amount;
}
void ship::modify_boost(float amount) {
    boost = glm::clamp(boost + amount, 0.f, max_boost);
}
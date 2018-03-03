//
// Created by Trevor Fisher on 2/13/2018.
//

#include "world.h"
#include "gtc/matrix_transform.hpp"
#include "collision_handler.h"
#include "engine/math_utils.h"
#include "entities/asteroid.h"
#include "entities/ship.h"
#include "entities/sinistar.h"
#include "controllers/worker_controller.h"
#include "controllers/soldier_controller.h"
#include "controllers/player_controller.h"
#include "campaign.h"
#include "controllers/scavenger_controller.h"

const int ATTRIBUTE_VERTEX_COUNT = 5;
bool mark_for_update = false;

world::world() { }
world::~world() {
    //TODO: delete causes program crash
    /*for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }*/
    entities.clear();
}

void world::update(float dt) {
    //Update each individual entity in the world
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(dt);

        if (entities[i]->do_destroy) {
            //TODO: Refactor to ensure cleanup (smart pointers?)
            //delete entities[i];
            entities.erase(entities.begin() + i);
            mark_for_update = true;

            i--;
            continue;
        }

        //Check for collisions with other entities
        //TODO: Optimize this by investigating quad trees
        for (int k = 0; k < entities.size(); k++) {
            glm::vec2 collision_point = glm::vec2(0.f);
            if (i != k && collides_with(*entities[i], *entities[k], collision_point)) {
                resolve_collision(*entities[i], *entities[k], collision_point);

                //TODO: Should both entities handle collision here?
                entities[i]->handle_collision(*entities[k], collision_point);
                entities[k]->handle_collision(*entities[i], collision_point);

                mark_for_update = true;
            }
        }
    }

    //Update game buffer if flag is marked
    if (mark_for_update) {
        update_buffer_data();
        mark_for_update = false;
    }
}
void world::draw(minalear::shader_program *shader) {
    glm::mat4 model = glm::mat4(1.f);

    glBindVertexArray(vao);
    int vertex_count = 0;
    for (int i = 0; i < entities.size(); i++) {
        model = glm::translate(glm::mat4(1.f), glm::vec3(entities[i]->position, 0.f)) *
                glm::rotate(glm::mat4(1.f), entities[i]->rotation, glm::vec3(0.f, 0.f, 1.f));
        shader->set_model_mat4(model);

        glDrawArrays(GL_LINE_LOOP, vertex_count, entities[i]->vertex_count);

        vertex_count += entities[i]->vertex_count;
    }
    glBindVertexArray(0);
}

void world::reset() {
    for (int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
    entities.clear();

}

void world::add_entity(game_entity *entity) {
    entity->game_world = this;
    entities.push_back(entity);

    mark_for_update = true;
}
void world::add_entities(game_entity *entities, int count) {
    for (int i = 0; i < count; i++) {
        add_entity(&entities[i]);
    }

    mark_for_update = true;
}

void world::generate_game_world() {
    //Create player
    ship *player_ship = new ship(new player_controller, ENTITY_TYPES::Player);
    player_ship->position = glm::vec2(GAME_WORLD_MAX / 2.f);
    add_entity(player_ship);

    //Add the bad boy
    add_entity(new sinistar(glm::vec2(0.f)));

    //Create asteroids
    for (int i = 0; i < NUM_ASTEROIDS; i++) {
        float x = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);
        float y = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);

        add_entity(new asteroid(glm::vec2(x, y)));
    }

    //Create workers
    for (int i = 0; i < NUM_WORKERS; i++) {
        //Randomly determine position
        float x = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);
        float y = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);

        ship *worker = new ship(new worker_controller, ENTITY_TYPES::Worker);
        worker->position = glm::vec2(x, y);

        add_entity(worker);
    }

    //Create soldiers
    for (int i = 0; i < NUM_SOLDIERS; i++) {
        //Randomly determine position
        float x = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);
        float y = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);

        ship *soldier = new ship(new soldier_controller, ENTITY_TYPES::Soldier);
        soldier->position = glm::vec2(x, y);

        add_entity(soldier);
    }

    //Create scavengers
    for (int i = 0; i < NUM_SCAVENGER; i++) {
        //Randomly determine position
        float x = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);
        float y = minalear::rand_float(GAME_WORLD_MIN, GAME_WORLD_MAX);

        ship *scavenger = new ship(new scavenger_controller, ENTITY_TYPES::Scavenger);
        scavenger->position = glm::vec2(x, y);

        add_entity(scavenger);
    }
}
void world::generate_buffer_data() {
    //Initialize VAO and VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float temp_buffer[5] = { 0.f, 0.f, 0.f, 0.f, 0.f };
    glBufferData(GL_ARRAY_BUFFER, sizeof(temp_buffer), temp_buffer, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); //Color

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, ATTRIBUTE_VERTEX_COUNT * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, ATTRIBUTE_VERTEX_COUNT * sizeof(float), (GLvoid*)(2 * sizeof(float)));

    update_buffer_data();

    glBindVertexArray(0);
}
void world::update_buffer_data() {
    //Count the total number of vertices for each game_entity
    int total_vertex_count = 0;
    for (int i = 0; i < entities.size(); i++) {
        total_vertex_count += entities[i]->vertex_count;
    }

    //Copy each entity's buffer data into a single VBO
    //TODO: Change this from 'new' to using a predefined, large array
    float *bufferData = new float[total_vertex_count * ATTRIBUTE_VERTEX_COUNT];

    int index = 0;
    for (int i = 0; i < entities.size(); i++) {
        for (int k = 0; k < entities[i]->vertex_count * ATTRIBUTE_VERTEX_COUNT; k++) {
            bufferData[index++] = entities[i]->buffer_data[k];
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * total_vertex_count * ATTRIBUTE_VERTEX_COUNT, bufferData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete[] bufferData;
}
void world::mark_world_for_update() {
    mark_for_update = true;
}

game_entity* world::find_entity(ENTITY_TYPES type) {
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i]->entity_type == type)
            return entities[i];
    }

    return nullptr;
}
game_entity* world::find_entity(ENTITY_TYPES type, glm::vec2 pos, float &dist) {
    game_entity *closest_entity = nullptr;
    float closest_dist = -1.f;

    for (int i = 0; i < entities.size(); i++) {
        if (entities[i]->entity_type == type) {
            dist = minalear::distance_square(entities[i]->position, pos);
            if (dist < closest_dist || closest_dist == -1.f) {
                closest_entity = entities[i];
                closest_dist = dist;
            }
        }
    }

    dist = sqrtf(closest_dist);
    return closest_entity;
}
bool world::check_collision(glm::vec2 pos, float radius, game_entity &entity, glm::vec2 &point) {
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i]->unique_id == entity.unique_id) continue;

        if (collides_with(*entities[i], pos, radius, point))
            return true;
    }

    return false;
}
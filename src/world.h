//
// Created by Trevor Fisher on 2/13/2018.
//

#ifndef SINISTAR_WORLD_H
#define SINISTAR_WORLD_H

#include <vector>
#include "entities/game_entity.h"
#include "engine/shader_program.h"

const int GAME_WORLD_MIN = 0;
const int GAME_WORLD_MAX = 8000;

const int NUM_ASTEROIDS = 240;
const int NUM_WORKERS = 12;
const int NUM_SOLDIERS = 8;

class world {
private:
    uint32_t vao, vbo;

    //TODO: Investigate smart pointers and implement a smart level initialize and cleanup
    std::vector<game_entity*> entities;

public:
    world();
    ~world();

    void update(float dt);
    void draw(minalear::shader_program *shader);

    void add_entity(game_entity *entity);
    void add_entities(game_entity *entities, int count);

    void generate_game_world();
    void generate_buffer_data();
    void update_buffer_data();
    void mark_world_for_update();

    game_entity* find_entity(ENTITY_TYPES type);
    game_entity* find_entity(ENTITY_TYPES type, glm::vec2 pos, float &dist);
    bool check_collision(glm::vec2 pos, float radius, game_entity &entity, glm::vec2 &point);
};


#endif //SINISTAR_WORLD_H

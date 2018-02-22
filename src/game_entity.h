//
// Created by Trevor Fisher on 2/8/2018.
//

#ifndef SINISTAR_GAME_ENTITY_H
#define SINISTAR_GAME_ENTITY_H

#include "glm.hpp"
//#include "world.h"

enum struct ENTITY_TYPES {
    Asteroid,
    Player,
    Worker,
    Soldier,
    Bullet,
    Sinistar,
    Sinibomb,
    Mineral
};
enum struct COLLISION_CATEGORIES {
    Player   = 1,
    Enemy    = 2,
    Asteroid = 4,
    Mineral  = 8,
    Ally_Bullet = 16,
    Enemy_Bullet = 32,
    All      = 255,
};

inline uint32_t operator | (COLLISION_CATEGORIES a, COLLISION_CATEGORIES b) {
    return (static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline uint32_t operator ^ (COLLISION_CATEGORIES a, COLLISION_CATEGORIES b) {
    return (static_cast<uint32_t>(a) ^ static_cast<uint32_t>(b));
}
inline uint32_t operator & (COLLISION_CATEGORIES a, COLLISION_CATEGORIES b) {
    return (static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

class game_entity {
private:
    static int next_valid_entity_id;

public:
    int unique_id;
    ENTITY_TYPES entity_type;
    class world *game_world;

    uint32_t collision_cat, collides_with;

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 force_accumulator;

    float rotation;
    float bounding_radius;
    float friction_coefficient;

    float *buffer_data;
    int vertex_count;

    bool do_destroy;

    game_entity();
    ~game_entity();
    
    virtual void update(float dt);
    virtual void apply_force(glm::vec2 force);
    virtual void handle_collision(const game_entity &other, glm::vec2 point);

    void set_collision_category(COLLISION_CATEGORIES category);
    void add_collision_type(COLLISION_CATEGORIES category);
};


#endif //SINISTAR_GAME_ENTITY_H

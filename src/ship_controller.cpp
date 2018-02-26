//
// Created by Trevor Fisher on 2/13/2018.
//

#include "ship_controller.h"
#include "ship.h"
#include "world.h"
#include "bullet.h"
#include <iostream>

ship_controller::ship_controller() {
    bullet_timer = 0.f;
}
void ship_controller::update(float dt) {
    bullet_timer += dt;
}
void ship_controller::on_damage(class game_entity &other, int amount) { }
void ship_controller::shoot(glm::vec2 pos, glm::vec2 vel) {
    bullet *entity_bullet = new bullet(pos, vel);

    //Determine bullet's collision
    entity_bullet->add_collision_type(COLLISION_CATEGORIES::Asteroid);
    if ((COLLISION_CATEGORIES::All & COLLISION_CATEGORIES::Player) == owner->collision_cat) {
        entity_bullet->set_collision_category(COLLISION_CATEGORIES::Ally_Bullet);
        entity_bullet->add_collision_type(COLLISION_CATEGORIES::Enemy);
    }
    else {
        entity_bullet->set_collision_category(COLLISION_CATEGORIES::Enemy_Bullet);
        entity_bullet->add_collision_type(COLLISION_CATEGORIES::Player);
    }

    owner->game_world->add_entity(entity_bullet);
    bullet_timer = 0.f;
}
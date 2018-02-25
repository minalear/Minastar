//
// Created by Trevor Fisher on 2/25/2018.
//

#include "soldier_controller.h"
#include "campaign.h"

soldier_controller::soldier_controller() {
    bullet_timer = 0.f;
    current_state = SOLDIER_STATES::Patrol;
}
void soldier_controller::update(float dt) {
    //Update timers
    bullet_timer += dt;

    if (current_state == SOLDIER_STATES::Patrol) {

    }
    else if (current_state == SOLDIER_STATES::Attack) {
        //Seek out and destroy the player
        game_entity *player_entity = campaign.player_entity;
        if (!player_entity) return; //Check if player pointer is valid


    }
    else if (current_state == SOLDIER_STATES::Defend) {

    }
}
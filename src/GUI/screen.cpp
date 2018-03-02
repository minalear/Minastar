//
// Created by Trevor Fisher on 3/1/2018.
//

#include "screen.h"

screen::screen(screen_manager *manager) {
    this->manager = manager;
}
screen::~screen() { }

void screen::update(float dt) { }
void screen::draw() { }
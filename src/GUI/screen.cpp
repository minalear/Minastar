//
// Created by Trevor Fisher on 3/1/2018.
//

#include "screen.h"

screen::screen(screen_manager *manager) {
    this->manager = manager;
}
screen::~screen() { }

void screen::on_activate() { }
void screen::on_deactivate() { }

void screen::update_fixed(float dt) { }
void screen::update_realtime() { }
void screen::draw() { }
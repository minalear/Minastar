//
// Created by Trevor Fisher on 3/1/2018.
//

#include "screen_manager.h"

screen_manager::screen_manager() { }
screen_manager::~screen_manager() { }

void screen_manager::attach_screen(const std::string name, screen *screen) {
    screens.insert({ name, screen });
}
void screen_manager::switch_screen(const std::string name) {
    //Ensure the index is contained in the map
    auto index = screens.find(name);
    if (index != screens.end()) {
        active_screen = index->second;
    }

    active_screen = screens[name];
}

void screen_manager::update_active_screen(float dt) {
    active_screen->update(dt);
}
void screen_manager::draw_active_screen() {
    active_screen->draw();
}
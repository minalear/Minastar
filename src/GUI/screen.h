//
// Created by Trevor Fisher on 3/1/2018.
//

#ifndef SINISTAR_SCREEN_H
#define SINISTAR_SCREEN_H

class screen {
public:
    class screen_manager *manager;

    screen(screen_manager *manager);
    ~screen();

    virtual void on_activate();
    virtual void on_deactivate();

    virtual void update_fixed(float dt);
    virtual void update_realtime();
    virtual void draw();
};

#endif //SINISTAR_SCREEN_H

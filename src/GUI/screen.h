//
// Created by Trevor Fisher on 3/1/2018.
//

#ifndef SINISTAR_SCREEN_H
#define SINISTAR_SCREEN_H

class screen {
private:
    class screen_manager *manager;

public:
    screen();
    ~screen();
    virtual void update(float dt);
    virtual void draw();
};

#endif //SINISTAR_SCREEN_H

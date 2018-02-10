//
// Created by Trevor Fisher on 2/3/2018.
//

#ifndef MINALEAR_WINDOW_H
#define MINALEAR_WINDOW_H

namespace minalear {
    void init_game_window(int windowWidth, int windowHeight);
    void init_opengl();
    void swap_buffers();
    float dt();
}

#endif //MINALEAR_WINDOW_H

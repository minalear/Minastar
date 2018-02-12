//
// Created by minalear on 2/9/2018.
//

#ifndef MINALEAR_INPUT_H
#define MINALEAR_INPUT_H

#include "glm.hpp"

namespace minalear {
    struct controller_state {
        glm::vec2 left_stick, right_stick;
        float left_stick_length, right_stick_length;
    };

    void init_input();
    void handle_input();

    controller_state* get_controller_state();
}

#endif //MINALEAR_INPUT_H

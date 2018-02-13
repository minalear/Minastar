//
// Created by minalear on 2/9/2018.
//

#ifndef MINALEAR_INPUT_H
#define MINALEAR_INPUT_H

#include "glm.hpp"



namespace minalear {
    enum struct JOYSTICK_BUTTONS {
        A = 0, //PS4 X
        B = 1, //PS4 O
        X = 2, //PS4 ■
        Y = 3, //PS4 ▲

        L1 = 4,
        L3 = 8,

        R1 = 5,
        R3 = 9,

        START = 7,
        SELECT = 6,
        GUIDE = 10

        //TODO: Button 11 is unidentified (for ps4 controller)
        //TODO: Determine best way to test for L2/R2 (trigger) button presses
    };

    struct controller_state {
        glm::vec2 left_stick, right_stick;
        float left_stick_length, right_stick_length;
    };

    void init_input();
    void handle_input();
    bool is_button_down(JOYSTICK_BUTTONS button);

    controller_state* get_controller_ptr();
}

#endif //MINALEAR_INPUT_H

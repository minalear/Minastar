//
// Created by Trevor Fisher on 2/24/2018.
//

#ifndef SINISTAR_BAR_H
#define SINISTAR_BAR_H

#include "glm.hpp"
#include "../engine/shader_program.h"

class bar_renderer {
private:
    uint32_t vao, vbo;
    float *buffer_data;

public:
    bar_renderer();
    ~bar_renderer();

    void draw_bar(minalear::shader_program *shader,
                  float value, float max,
                  glm::vec2 pos, glm::vec2 fill_size,
                  glm::vec3 bar_color, glm::vec3 fill_color);
};


#endif //SINISTAR_BAR_H

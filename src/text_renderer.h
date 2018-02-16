//
// Created by Trevor Fisher on 2/16/2018.
//

#ifndef SINISTAR_TEXT_RENDERER_H
#define SINISTAR_TEXT_RENDERER_H

#include <string>
#include "engine/font.h"
#include "engine/shader_program.h"
#include "glm.hpp"

class text_renderer {
private:
    uint32_t vao, vbo;

public:
    minalear::font *text_font;

    text_renderer(const std::string font_name);
    ~text_renderer();

    void draw_string(minalear::shader_program *text_shader, std::string str, glm::vec2 pos);
};


#endif //SINISTAR_TEXT_RENDERER_H

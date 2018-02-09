//
// Created by Trevor Fisher on 1/19/2018.
//

#ifndef MINALEAR_SHADER_H
#define MINALEAR_SHADER_H

#include "glad/glad.h"

namespace minalear {
    class shader_program {
    private:
        GLuint programID;

    public:
        shader_program(const char *, const char *);
        GLuint id();
        void use();
        void load_shaders(const char *, const char *);
    };
}

#endif //MINALEAR_SHADER_H

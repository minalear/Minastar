//
// Created by Trevor Fisher on 1/19/2018.
//

#ifndef MINALEAR_SHADER_H
#define MINALEAR_SHADER_H

#include "glad/glad.h"
#include "glm.hpp"

namespace minalear {
    class shader_program {
    private:
        GLuint programID;

        //TODO: Make this more robust and generic
        int32_t projLoc, viewLoc, modelLoc;

    public:
        shader_program(const char *, const char *);
        GLuint id();
        void use();
        void load_shaders(const char *, const char *);

        void init_uniforms();
        void set_proj_mat4(const glm::mat4 &proj);
        void set_view_mat4(const glm::mat4 &view);
        void set_model_mat4(const glm::mat4 &model);
    };
}

#endif //MINALEAR_SHADER_H

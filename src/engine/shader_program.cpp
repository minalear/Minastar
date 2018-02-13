//
// Created by Trevor Fisher on 1/19/2018.
//

#include <cstdio>
#include "glad/glad.h"
#include "shader_program.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

bool checkShaderCompilation(GLuint shaderID) {
    GLint compileStatus = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {

        GLchar errorMessage[512];
        glGetShaderInfoLog(shaderID, 512, NULL, errorMessage);
        printf("Shader Compilation Error, %s\n", errorMessage);
    }
}

minalear::shader_program::shader_program(const char *vertexSource, const char *fragmentSource) {
    programID = glCreateProgram();
    load_shaders(vertexSource, fragmentSource);
}
GLuint minalear::shader_program::id() {
    return programID;
}
void minalear::shader_program::use() {
    glUseProgram(programID);
}
void minalear::shader_program::load_shaders(const char *vertexSource, const char *fragmentSource) {
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderID);
    checkShaderCompilation(vertexShaderID);

    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShaderID);
    checkShaderCompilation(fragmentShaderID);

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

void minalear::shader_program::init_uniforms() {
    projLoc  = glGetUniformLocation(programID, "proj");
    viewLoc  = glGetUniformLocation(programID, "view");
    modelLoc = glGetUniformLocation(programID, "model");
}
void minalear::shader_program::set_proj_mat4(const glm::mat4 &proj) {
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
}
void minalear::shader_program::set_view_mat4(const glm::mat4 &view) {
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}
void minalear::shader_program::set_model_mat4(const glm::mat4 &model) {
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}
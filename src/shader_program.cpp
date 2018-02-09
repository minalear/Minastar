//
// Created by Trevor Fisher on 1/19/2018.
//

#include <cstdio>
#include "glad/glad.h"
#include "shader_program.h"

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
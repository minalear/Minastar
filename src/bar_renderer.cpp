//
// Created by Trevor Fisher on 2/24/2018.
//

#include "bar_renderer.h"
#include "gtc/matrix_transform.hpp"
#include "glad/glad.h"

//6 points with 5 attributes
const int BUFFER_DATA_LENGTH = 6 * 5;

bar_renderer::bar_renderer() {
    //Initialize buffer data
    buffer_data = new float[BUFFER_DATA_LENGTH];

    //region /* Rectangle Point Data */
    buffer_data[0 * 5 + 0] = 0.f;
    buffer_data[0 * 5 + 1] = 0.f;

    buffer_data[1 * 5 + 0] = 0.f;
    buffer_data[1 * 5 + 1] = 1.f;

    buffer_data[2 * 5 + 0] = 1.f;
    buffer_data[2 * 5 + 1] = 0.f;


    buffer_data[3 * 5 + 0] = 1.f;
    buffer_data[3 * 5 + 1] = 0.f;

    buffer_data[4 * 5 + 0] = 0.f;
    buffer_data[4 * 5 + 1] = 1.f;

    buffer_data[5 * 5 + 0] = 1.f;
    buffer_data[5 * 5 + 1] = 1.f;
    //endregion /* Rectangle Point Data */

    //VAO and VBO init
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BUFFER_DATA_LENGTH, buffer_data, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); //Color

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
bar_renderer::~bar_renderer() {
    delete[] buffer_data;
}

void set_rect_color(float *buffer_data, glm::vec3 bar_color) {
    for (int i = 0; i < 6; i++) {
        buffer_data[i * 5 + 2] = bar_color.r;
        buffer_data[i * 5 + 3] = bar_color.g;
        buffer_data[i * 5 + 4] = bar_color.b;
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * BUFFER_DATA_LENGTH, buffer_data, GL_DYNAMIC_DRAW);
}
void bar_renderer::draw_bar(minalear::shader_program *shader,
                            float value, float max,
                            glm::vec2 pos, glm::vec2 fill_size,
                            glm::vec3 bar_color, glm::vec3 fill_color)
{
    shader->use();
    glBindVertexArray(vao);

    //Draw base rectangle
    glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(pos, 1.f)) *
                      glm::scale(glm::mat4(1.f), glm::vec3(fill_size, 1.f));

    shader->set_model_mat4(model);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    set_rect_color(buffer_data, fill_color);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Draw bar
    float percent = value / max;
    model = glm::translate(glm::mat4(1.f), glm::vec3(pos, 1.f)) *
            glm::scale(glm::mat4(1.f), glm::vec3(fill_size.x * percent, fill_size.y, 1.f));
    shader->set_model_mat4(model);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    set_rect_color(buffer_data, bar_color);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
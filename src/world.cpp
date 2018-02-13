//
// Created by Trevor Fisher on 2/13/2018.
//

#include "world.h"
#include "gtc/matrix_transform.hpp"

const int ATTRIBUTE_VERTEX_COUNT = 5;

world::world() {

}
world::~world() {
    entities.clear();
}

void world::update(float dt) {
    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(dt);
    }
}
void world::draw(minalear::shader_program *shader) {
    glm::mat4 model = glm::mat4(1.f);

    int vertex_count = 0;
    for (int i = 0; i < entities.size(); i++) {
        model = glm::translate(glm::mat4(1.f), glm::vec3(entities[i]->position, 0.f)) *
                glm::rotate(glm::mat4(1.f), entities[i]->rotation, glm::vec3(0.f, 0.f, 1.f));
        shader->set_model_mat4(model);

        glDrawArrays(GL_LINE_LOOP, vertex_count, entities[i]->vertex_count);

        vertex_count += entities[i]->vertex_count;
    }
}

void world::add_entity(game_entity *entity) {
    entities.push_back(entity);
}
void world::add_entities(game_entity *entities, int count) {
    for (int i = 0; i < count; i++) {
        add_entity(&entities[i]);
    }
}

void world::generate_buffer_data() {
    //Count the total number of vertices for each game_entity
    int total_vertex_count = 0;
    for (int i = 0; i < entities.size(); i++) {
        total_vertex_count += entities[i]->vertex_count;
    }

    //Copy each entity's buffer data into a single VBO
    float *bufferData = new float[total_vertex_count * ATTRIBUTE_VERTEX_COUNT];

    int index = 0;
    for (int i = 0; i < entities.size(); i++) {
        for (int k = 0; k < entities[i]->vertex_count * ATTRIBUTE_VERTEX_COUNT; k++) {
            bufferData[index++] = entities[i]->buffer_data[k];
        }
    }

    //Initialize VAO and VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * total_vertex_count * 5, bufferData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); //Position
    glEnableVertexAttribArray(1); //Color

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

    //Cleanup
    delete[] bufferData;
}
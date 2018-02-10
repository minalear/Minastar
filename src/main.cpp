#include <random>
#include <ctime>
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "filer_handler.h"
#include "window.h"
#include "shader_program.h"
#include "asteroid.h"
#include "ship.h"

const int NUM_ASTEROIDS = 5;
const int NUM_SHIPS = 1;

void init_buffer_data(asteroid *asteroids, ship *ships, uint32_t &vao, uint32_t &vbo) {
    //Count the total number of vertices for each game_entity
    int total_vertex_count = 0;
    for (int i = 0; i < NUM_ASTEROIDS; i++) {
        total_vertex_count += asteroids[i].vertex_count;
    }
    for (int i = 0; i < NUM_SHIPS; i++) {
        total_vertex_count += ships[i].vertex_count;
    }

    //Copy each game_entity's buffer data into a single VBO
    float *bufferData = new float[total_vertex_count * 5];

    int index = 0;
    for (int i = 0; i < NUM_ASTEROIDS; i++) {
        for (int k = 0; k < asteroids[i].vertex_count * 5; k++) {
            bufferData[index++] = asteroids[i].buffer_data[k];
        }
    }
    for (int i = 0; i < NUM_SHIPS; i++) {
        for (int k = 0; k < ships[i].vertex_count * 5; k++) {
            bufferData[index++] = ships[i].buffer_data[k];
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

    //Delete buffer
    delete[] bufferData;
}

int main(int argc, char *argv[]) {
    //Initialize SDL and OpenGL
    minalear::init_game_window(800, 450);
    minalear::init_opengl();

    //Setup OpenGL settings
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);

    glEnable(GL_LINE_SMOOTH);
    //glEnable(GL_POLYGON_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Seed random number generator
    srand((unsigned int)time(NULL));

    //Initialize VAO and VBO buffers
    uint32_t vao, vbo;
    asteroid asteroids[NUM_ASTEROIDS];
    ship ships[NUM_SHIPS];

    ship *player = &ships[0];

    init_buffer_data(asteroids, ships, vao, vbo);

    //Initialize shader program
    minalear::shader_program shader(
            minalear::readFile("shaders/basic_vertex.glsl"),
            minalear::readFile("shaders/basic_frag.glsl"));
    shader.use();

    //Set uniform location addresses
    int32_t modelLoc, projLoc, viewLoc;
    projLoc  = glGetUniformLocation(shader.id(), "proj");
    viewLoc  = glGetUniformLocation(shader.id(), "view");
    modelLoc = glGetUniformLocation(shader.id(), "model");

    //Initialize matrices
    glm::mat4 proj, view, model;
    proj  = glm::ortho(0.f, 800.f, 450.f, 0.f, -1.f, 1.f);
    view  = glm::mat4(1.f);
    model = glm::mat4(1.f);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    //Setup controller input
    SDL_Joystick *joystick;
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    //Begin main game loop
    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            //Break out of game loop
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        float dt = minalear::dt();

        glClear(GL_COLOR_BUFFER_BIT);

        glm::vec2 player_force = glm::vec2(0.f);
        int x_axis = SDL_JoystickGetAxis(joystick, 0);
        int y_axis = SDL_JoystickGetAxis(joystick, 1);

        if (x_axis < -8000.f || x_axis > 8000.f)
            player_force.x = x_axis / 65536.f;
        if (y_axis < -8000.f || y_axis > 8000.f)
            player_force.y = y_axis / 65536.f;

        const float PLAYER_FORCE_FACTOR = 10.f;
        player->apply_force(player_force * PLAYER_FORCE_FACTOR);
        player->update(dt);

        if (player_force.length() != 0.f)
            player->rotation = atan2f(player_force.y, player_force.x);

        int vertex_count = 0;
        for (int i = 0; i < NUM_ASTEROIDS; i++) {
            asteroids[i].rotation += 0.1f * dt;
            model = glm::translate(glm::mat4(1.f), glm::vec3(asteroids[i].position, 0.f)) *
                    glm::rotate(glm::mat4(1.f), asteroids[i].rotation, glm::vec3(0.f, 0.f, 1.f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_LINE_LOOP, vertex_count, asteroids[i].vertex_count);
            vertex_count += asteroids[i].vertex_count;
        }
        for (int i = 0; i < NUM_SHIPS; i++) {
            model = glm::translate(glm::mat4(1.f), glm::vec3(ships[i].position, 0.f)) *
                    glm::rotate(glm::mat4(1.f), ships[i].rotation, glm::vec3(0.f, 0.f, 1.f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glDrawArrays(GL_LINE_LOOP, vertex_count, ships[i].vertex_count);
            vertex_count += ships[i].vertex_count;
        }

        minalear::swap_buffers();

        //TODO: look into laggy joystick input
        SDL_FlushEvent(SDL_JOYAXISMOTION);
    } //end main game loop

    return 0;
}
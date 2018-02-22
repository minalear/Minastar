//
// Created by Trevor Fisher on 2/21/2018.
//

#include "math_utils.h"
#include <random>

int minalear::rand_int(int min, int max) {
    return (rand() / RAND_MAX) * (max - min) + min;
}
float minalear::rand_float(float min, float max) {
    return (rand() / (float)RAND_MAX) * (max - min) + min;
}
float minalear::distance(glm::vec2 a, glm::vec2 b) {
    return sqrtf(distance_square(a, b));
}
float minalear::distance_square(glm::vec2 a, glm::vec2 b) {
    float x_sqr = (b.x - a.x) * (b.x - a.x);
    float y_sqr = (b.y - a.y) * (b.y - a.y);

    return x_sqr + y_sqr;
}
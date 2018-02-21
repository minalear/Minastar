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
    return sqrtf(powf(b.x - a.x, 2.f) + powf(b.y - a.y, 2.f));
}
float minalear::distance_square(glm::vec2 a, glm::vec2 b) {
    return powf(b.x - a.x, 2.f) + powf(b.y - a.y, 2.f);
}
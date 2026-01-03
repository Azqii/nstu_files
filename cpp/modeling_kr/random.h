#ifndef MODELING_KR_RANDOM_H
#define MODELING_KR_RANDOM_H

#include <cstdlib>
#include <cmath>

inline int get_uniform(int mean, int offset) {
    return mean - offset + rand() % (2 * offset + 1);
}

inline float get_exp(float lambda) {
    float u = (float)(rand() % 32768) / 32768.0f;
    if (u < 0.0001f) u = 0.0001f;
    return -log(u) / lambda;
}

#endif //MODELING_KR_RANDOM_H

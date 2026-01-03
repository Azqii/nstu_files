#ifndef MODELING_KR_NORMAL_H
#define MODELING_KR_NORMAL_H

#include <cmath>

inline float normal_pdf(float mean, float disp, float x) {
    return (1.0f / (disp * sqrt(2 * M_PI))) * exp(-((x - mean) * (x - mean)) / (2 * disp * disp));
}

inline float simpson(float A, float B, float mean, float disp) {
    float h = 0.01f;
    float s = 0;
    float h1 = h / 1.5f;
    float k1 = normal_pdf(mean, disp, A);
    
    for (float x = A; (x < B) && ((x + h - B) <= h1); x = x + h) {
        float k2 = normal_pdf(mean, disp, x + h / 2);
        float k3 = normal_pdf(mean, disp, x + h);
        s = s + k1 + 4 * k2 + k3;
        k1 = k3;
    }
    return s * h / 6;
}

inline float equ(float bottom_bound, float top_bound, float mean, float disp, float almost_all, float eps, float right) {
    float original_bottom = bottom_bound;
    while ((top_bound - bottom_bound) > eps) {
        float mid = (bottom_bound + top_bound) / 2;
        float val = simpson(original_bottom, mid, mean, disp) / almost_all;
        if (val < right)
            bottom_bound = mid;
        else
            top_bound = mid;
    }
    return (bottom_bound + top_bound) / 2;
}

inline float get_normal(float mean, float disp, float eps) {
    float bottom_bound = mean - disp * sqrt(-log(2 * M_PI * eps * eps * disp * disp));
    float top_bound = mean + disp * sqrt(-log(2 * M_PI * eps * eps * disp * disp));
    float almost_all = simpson(bottom_bound, top_bound, mean, disp);
    int r_num = rand() % 32768;
    float right = (float)r_num / 32768.0f;
    return equ(bottom_bound, top_bound, mean, disp, almost_all, eps, right);
}

#endif //MODELING_KR_NORMAL_H

#pragma once

const float INFINITY_F = std::numeric_limits<float>::infinity();
const float EPSILON = .00001f;
const float PI = 3.1415926535897932385f;

inline float degreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
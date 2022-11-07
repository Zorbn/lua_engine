#pragma once

#include <cinttypes>
#include <glm/glm.hpp>

class camera {
public:
    void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b);
    void setBackgroundColorNormalized(float r, float g, float b);

    float x = 0;
    float y = 0;
    float z = 0;

    float background_r = 0.0f;
    float background_g = 0.0f;
    float background_b = 0.0f;
    float background_a = 1.0f;

    float fov = 90.0f;
};
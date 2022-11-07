#include "camera.hpp"

void camera::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b) {
    background_r = static_cast<float>(r) / 255.0f;
    background_g = static_cast<float>(g) / 255.0f;
    background_b = static_cast<float>(b) / 255.0f;
    background_a = 1.0f;
}

void camera::setBackgroundColorNormalized(float r, float g, float b) {
    background_r = r;
    background_g = g;
    background_b = b;
    background_a = 1.0f;
}
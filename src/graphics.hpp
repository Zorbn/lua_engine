#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cinttypes>
#include <string>
#include <unordered_set>

#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "texture_array.hpp"

class graphics {
public:
    graphics(const std::string& window_name, int32_t window_width, int32_t window_height);
    void close_window();
    bool window_is_running();

    static void resize_callback(GLFWwindow* window, int32_t new_width, int32_t new_height);
    void on_resize(int32_t new_width, int32_t new_height);
    static void key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
    void on_key(int32_t key, int32_t scancode, int32_t action, int32_t mods);

    bool is_key_held(int32_t key);
    bool was_key_pressed(int32_t key);
    bool was_key_released(int32_t key);

    model create_model(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
    void begin_drawing(camera& camera, shader& shader);
    void draw_sprite_array();
    void draw_sprite(texture_array& texture_array, const std::string& texture_name, shader& shader);
    void draw_model();
    void draw_model_array();
    void end_drawing();

private:
    GLFWwindow* window;
    int32_t window_width;
    int32_t window_height;
    model default_sprite_model;
    std::unordered_set<int32_t> held_keys;
    std::unordered_set<int32_t> pressed_keys;
    std::unordered_set<int32_t> released_keys;
};
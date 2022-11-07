#include "graphics.hpp"
#include <stdexcept>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

const std::vector<float> sprite_model_vertices = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
};

const std::vector<uint32_t> sprite_model_indices = {
    0, 1, 3,
    0, 3, 2,
};

graphics::graphics(const std::string& window_name, int32_t window_width, int32_t window_height) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(window_width, window_height, window_name.c_str(), nullptr, nullptr);

    if (!window) {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, window_width, window_height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    this->window_width = window_width;
    this->window_height = window_height;

    default_sprite_model = create_model(sprite_model_vertices, sprite_model_indices);
}

void graphics::close_window() {
    glfwTerminate();
}

bool graphics::window_is_running() {
    return !glfwWindowShouldClose(window);
}

void graphics::on_resize(int32_t new_width, int32_t new_height) {
    window_width = new_width;
    window_height = new_height;
    glViewport(0, 0, new_width, new_height);
}

void graphics::on_key(int32_t key, int32_t scancode, int32_t action, int32_t mods) {
    if (action == GLFW_PRESS) {
        pressed_keys.insert(key);
        held_keys.insert(key);
    } else if (action == GLFW_RELEASE) {
        released_keys.insert(key);
        held_keys.erase(key);
    }
}

void graphics::resize_callback(GLFWwindow* window, int32_t new_width, int32_t new_height) {
    static_cast<graphics*>(glfwGetWindowUserPointer(window))->on_resize(new_width, new_height);
}

void graphics::key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
    static_cast<graphics*>(glfwGetWindowUserPointer(window))->on_key(key, scancode, action, mods);
}

bool graphics::is_key_held(int32_t key) {
    return held_keys.find(key) != held_keys.end();
}

bool graphics::was_key_pressed(int32_t key) {
    return pressed_keys.find(key) != pressed_keys.end();
}

bool graphics::was_key_released(int32_t key) {
    return released_keys.find(key) != released_keys.end();
}

void graphics::begin_drawing(camera& camera, shader& shader) {
    glm::mat4 view = glm::lookAt(glm::vec3(camera.x, camera.y, camera.z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 proj = glm::perspective(glm::radians(camera.fov), static_cast<float>(window_width) / static_cast<float>(window_height), 0.01f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);

    shader.use();

    shader.set_uniform_matrix4fv("proj", 1, GL_FALSE, glm::value_ptr(proj));
    shader.set_uniform_matrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));
    shader.set_uniform_matrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));

    glClearColor(camera.background_r, camera.background_g, camera.background_b, camera.background_a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

model graphics::create_model(const std::vector<float>& vertices, const std::vector<uint32_t>& indices) {
    uint32_t vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    uint32_t ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    return model {
        vao,
        vbo,
        ebo,
        indices.size(),
    };
}

void graphics::draw_sprite_array() {

}

// TODO: Get rid of shader being passed to draw, instead use instance buffer data.
void graphics::draw_sprite(texture_array& texture_array, const std::string& texture_name, shader& shader) {
    texture_array.use();
    glBindVertexArray(default_sprite_model.vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, default_sprite_model.ebo);

    int32_t tex_index_loc = shader.uniform_location("texture_index");
    glUniform1i(tex_index_loc, texture_array.get_texture(texture_name));

    glDrawElements(GL_TRIANGLES, default_sprite_model.index_count, GL_UNSIGNED_INT, (GLsizei)0);
}

void graphics::draw_model() {

}

void graphics::draw_model_array() {

}

void graphics::end_drawing() {
    glfwSwapBuffers(window);
    pressed_keys.clear();
    released_keys.clear();
    glfwPollEvents();
}
#include "texture_array.hpp"

#include <iostream>
#include <glad/glad.h>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

texture_array::texture_array(std::vector<std::string> images) {
    size_t image_count = images.size();

    if (image_count < 1) {
        std::cout << "No images supplied when creating texture array" << std::endl;
        exit(1);
    }

    stbi_set_flip_vertically_on_load(true);

    int32_t width;
    int32_t height;
    uint8_t* data;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    for (int32_t i = 0; i < images.size(); i++) {
        std::cout << images[i] << std::endl;
        int32_t i_width;
        int32_t i_height;
        int32_t i_channel_count;
        data = stbi_load(images[i].c_str(), &i_width, &i_height, &i_channel_count, 0);

        if (!data) {
            std::cout << "Failed to load: " << images[i] << std::endl;
            exit(1);
        }

        GLint format = GL_RGBA;

        switch (i_channel_count) {
            case 4:
                break;
            case 3:
                format = GL_RGB;
                break;
            default:
                std::cout << "Unsupported image type loaded: " << images[i] << std::endl;
                break;
        }

        if (i == 0) {
            width = i_width;
            height = i_height;

            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, width, height, images.size(), 0, format, GL_UNSIGNED_BYTE, nullptr);
        } else if (i_width != width || i_height != height) {
            std::cout << "Can't create an array of different sized textures" << std::endl;
            exit(1);
        }

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, format, GL_UNSIGNED_BYTE, data);

        texture_indices.insert(std::make_pair(images[i], i));
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

texture_array::~texture_array() {
    std::cout << "yeet" << std::endl;
    glDeleteTextures(1, &texture);
}

size_t texture_array::get_texture(const std::string& name) {
    if (texture_indices.find(name) == texture_indices.end()) {
        std::cout << "Couldn't find texture in array: " << name << std::endl;
        exit(1);
    }

    return texture_indices[name];
}

void texture_array::use() {
    glBindTexture(GL_TEXTURE_2D, texture);
}
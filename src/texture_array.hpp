#pragma once

#include <unordered_map>
#include <vector>
#include <cinttypes>
#include <sol/sol.hpp>

class texture_array {
public:
    texture_array(std::vector<std::string> images);
    ~texture_array();

    size_t get_texture(const std::string& name);
    void use();

private:
    uint32_t texture;
    std::unordered_map<std::string, size_t> texture_indices;
};
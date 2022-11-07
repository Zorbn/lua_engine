#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string string_from_file(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
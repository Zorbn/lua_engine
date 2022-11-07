cmake_minimum_required(VERSION 3.17)
project(EmbeddingLua)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS FALSE)

add_subdirectory(deps/lua)
add_subdirectory(deps/glad)
add_subdirectory(deps/glfw-3.3.8)
add_subdirectory(deps/glm)

add_executable(EmbeddingLua src/main.cpp
    src/graphics.cpp src/graphics.hpp
    src/camera.cpp src/camera.hpp
    src/shader.cpp src/shader.hpp
    src/texture_array.cpp src/texture_array.hpp
    src/model.hpp
    src/utils.hpp
)

target_include_directories(EmbeddingLua PUBLIC ${CMAKE_SOURCE_DIR}/deps/stb_image ${CMAKE_SOURCE_DIR}/deps/sol2)
target_link_libraries(EmbeddingLua lua_static glad glfw glm)

#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 tex_coord;

out vec2 vert_tex_coord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 proj;

void main() {
    vert_tex_coord = tex_coord;
    gl_Position = proj * view * model * vec4(in_pos, 1.0);
}
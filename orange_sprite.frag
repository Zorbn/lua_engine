#version 330 core

in vec2 vert_tex_coord;

out vec4 frag_color;

uniform sampler2DArray texture_array;
uniform int texture_index;

void main() {
    frag_color = vec4(1.0, 0.5, 0.0, 1.0);

    if (frag_color.a < 1.0) {
        discard;
    }
}
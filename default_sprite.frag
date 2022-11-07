#version 330 core

in vec2 vert_tex_coord;

out vec4 frag_color;

uniform sampler2DArray texture_array;
uniform int texture_index;

void main() {
    frag_color = texture(texture_array, vec3(vert_tex_coord, float(texture_index)));

    if (frag_color.a < 1.0) {
        discard;
    }
}
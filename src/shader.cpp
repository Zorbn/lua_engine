#include "shader.hpp"
#include "utils.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>

const int32_t max_shader_error_len = 1024;

shader::shader() : shader(string_from_file("default_sprite.vert"), string_from_file("default_sprite.frag")) {}

shader::shader(const std::string& vertex_code, const std::string& fragment_code) {
    const char* vertex_code_c_str = vertex_code.c_str();
    const char* fragment_code_c_str = fragment_code.c_str();

    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_code_c_str, nullptr);
    glCompileShader(vertex_shader);
    check_shader_compile_error(vertex_shader);

    uint32_t fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_code_c_str, nullptr);
    glCompileShader(fragment_shader);
    check_shader_compile_error(fragment_shader);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    check_shader_link_error(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

shader shader::from_file(const std::string& vertex_path, const std::string& fragment_path) {
    std::string vertex_code = string_from_file(vertex_path);
    std::string fragment_code = string_from_file(fragment_path);

    return shader(vertex_code, fragment_code);
}

void shader::check_shader_compile_error(uint32_t shader) {
    int32_t success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char info_log[max_shader_error_len];
        glGetShaderInfoLog(shader, max_shader_error_len, nullptr, info_log);
        std::cout << info_log << std::endl;
        exit(1);
    }
}

void shader::check_shader_link_error(uint32_t program) {
    int32_t success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char info_log[max_shader_error_len];
        glGetProgramInfoLog(program, max_shader_error_len, nullptr, info_log);
        std::cout << info_log << std::endl;
        exit(1);
    }
}

void shader::use() {
    glUseProgram(shader_program);
}

int32_t shader::uniform_location(const std::string& name) {
    auto found = uniform_locations.find(name);

    if (found != uniform_locations.end()) {
        return uniform_locations[name];
    }

    int32_t location = glGetUniformLocation(shader_program, name.c_str());

    uniform_locations.insert(std::make_pair(name, location));

    return location;
}

bool shader::set_uniform1f(const std::string& name, GLfloat v0) {
    _TRY_SET_UNIFORM(glUniform1f(location, v0));
}

bool shader::set_uniform2f(const std::string& name, GLfloat v0, GLfloat v1) {
    _TRY_SET_UNIFORM(glUniform2f(location, v0, v1));
}

bool shader::set_uniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) {
    _TRY_SET_UNIFORM(glUniform3f(location, v0, v1, v2));
}

bool shader::set_uniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    _TRY_SET_UNIFORM(glUniform4f(location, v0, v1, v2, v3));
}

bool shader::set_uniform1i(const std::string& name, GLint v0) {
    _TRY_SET_UNIFORM(glUniform1i(location, v0));
}

bool shader::set_uniform2i(const std::string& name, GLint v0, GLint v1) {
    _TRY_SET_UNIFORM(glUniform2i(location, v0, v1));
}

bool shader::set_uniform3i(const std::string& name, GLint v0, GLint v1, GLint v2) {
    _TRY_SET_UNIFORM(glUniform3i(location, v0, v1, v2));
}

bool shader::set_uniform4i(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3) {
    _TRY_SET_UNIFORM(glUniform4i(location, v0, v1, v2, v3));
}

bool shader::set_uniform1ui(const std::string& name, GLuint v0) {
    _TRY_SET_UNIFORM(glUniform1ui(location, v0));
}

bool shader::set_uniform2ui(const std::string& name, GLuint v0, GLuint v1) {
    _TRY_SET_UNIFORM(glUniform2ui(location, v0, v1));
}

bool shader::set_uniform3ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2) {
    _TRY_SET_UNIFORM(glUniform3ui(location, v0, v1, v2));
}

bool shader::set_uniform4ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    _TRY_SET_UNIFORM(glUniform4ui(location, v0, v1, v2, v3));
}

bool shader::set_uniform1fv(const std::string& name, GLsizei count, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniform1fv(location, count, value));
}

bool shader::set_uniform2fv(const std::string& name, GLsizei count, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniform2fv(location, count, value));
}

bool shader::set_uniform3fv(const std::string& name, GLsizei count, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniform3fv(location, count, value));
}

bool shader::set_uniform4fv(const std::string& name, GLsizei count, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniform4fv(location, count, value));
}

bool shader::set_uniform1iv(const std::string& name, GLsizei count, const GLint *value) {
    _TRY_SET_UNIFORM(glUniform1iv(location, count, value));
}

bool shader::set_uniform2iv(const std::string& name, GLsizei count, const GLint *value) {
    _TRY_SET_UNIFORM(glUniform2iv(location, count, value));
}

bool shader::set_uniform3iv(const std::string& name, GLsizei count, const GLint *value) {
    _TRY_SET_UNIFORM(glUniform3iv(location, count, value));
}

bool shader::set_uniform4iv(const std::string& name, GLsizei count, const GLint *value) {
    _TRY_SET_UNIFORM(glUniform4iv(location, count, value));
}

bool shader::set_uniform1uiv(const std::string& name, GLsizei count, const GLuint *value) {
    _TRY_SET_UNIFORM(glUniform1uiv(location, count, value));
}

bool shader::set_uniform2uiv(const std::string& name, GLsizei count, const GLuint *value) {
    _TRY_SET_UNIFORM(glUniform2uiv(location, count, value));
}

bool shader::set_uniform3uiv(const std::string& name, GLsizei count, const GLuint *value) {
    _TRY_SET_UNIFORM(glUniform3uiv(location, count, value));
}

bool shader::set_uniform4uiv(const std::string& name, GLsizei count, const GLuint *value) {
    _TRY_SET_UNIFORM(glUniform4uiv(location, count, value));
}

bool shader::set_uniform_matrix2fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix2fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix3fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix4fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix2x3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix2x3fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix3x2fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix3x2fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix2x4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix2x4fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix4x2fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix4x2fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix3x4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix3x4fv(location, count, transpose, value));
}

bool shader::set_uniform_matrix4x3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value) {
    _TRY_SET_UNIFORM(glUniformMatrix4x3fv(location, count, transpose, value));
}

shader::~shader() {
    std::cout << "Also yeet" << std::endl;
}
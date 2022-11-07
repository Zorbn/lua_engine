#pragma once

#include <cinttypes>
#include <string>
#include <unordered_map>
#include <glad/glad.h>

#define _TRY_SET_UNIFORM(f) { \
    use(); \
    int32_t location = uniform_location(name); \
    if (location == -1) { return false; } \
    f; \
    return true; \
}

class shader {
public:
    shader();
    ~shader();
    shader(const std::string& vertex_code, const std::string& fragment_code);
    static shader from_file(const std::string& vertex_path, const std::string& fragment_path);
    void use();
    int32_t uniform_location(const std::string& name);

    bool set_uniform1f(const std::string& name, GLfloat v0);
    bool set_uniform2f(const std::string& name, GLfloat v0, GLfloat v1);
    bool set_uniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2);
    bool set_uniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    bool set_uniform1i(const std::string& name, GLint v0);
    bool set_uniform2i(const std::string& name, GLint v0, GLint v1);
    bool set_uniform3i(const std::string& name, GLint v0, GLint v1, GLint v2);
    bool set_uniform4i(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3);
    bool set_uniform1ui(const std::string& name, GLuint v0);
    bool set_uniform2ui(const std::string& name, GLuint v0, GLuint v1);
    bool set_uniform3ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2);
    bool set_uniform4ui(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    bool set_uniform1fv(const std::string& name, GLsizei count, const GLfloat *value);
    bool set_uniform2fv(const std::string& name, GLsizei count, const GLfloat *value);
    bool set_uniform3fv(const std::string& name, GLsizei count, const GLfloat *value);
    bool set_uniform4fv(const std::string& name, GLsizei count, const GLfloat *value);
    bool set_uniform1iv(const std::string& name, GLsizei count, const GLint *value);
    bool set_uniform2iv(const std::string& name, GLsizei count, const GLint *value);
    bool set_uniform3iv(const std::string& name, GLsizei count, const GLint *value);
    bool set_uniform4iv(const std::string& name, GLsizei count, const GLint *value);
    bool set_uniform1uiv(const std::string& name, GLsizei count, const GLuint *value);
    bool set_uniform2uiv(const std::string& name, GLsizei count, const GLuint *value);
    bool set_uniform3uiv(const std::string& name, GLsizei count, const GLuint *value);
    bool set_uniform4uiv(const std::string& name, GLsizei count, const GLuint *value);
    bool set_uniform_matrix2fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix2x3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix3x2fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix2x4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix4x2fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix3x4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);
    bool set_uniform_matrix4x3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat *value);

private:
    static void check_shader_compile_error(uint32_t shader);
    static void check_shader_link_error(uint32_t shader);

    uint32_t shader_program;
    std::unordered_map<std::string, int32_t> uniform_locations;
};
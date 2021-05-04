/**
\file        Shader.h
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/
#pragma once

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace FindersEngine
{
    class Shader
    {
    public:
        // read/build the shader
        Shader() {}
        ~Shader() {}
        void init(const GLchar* vertex_path, const GLchar* fragment_path);
        void draw_begin();
        void draw_end();
        void setFloat(const std::string& name, GLfloat value) const;
        void setInt(const std::string& name, GLuint value) const;
        void setVec2f(const std::string& name, const glm::vec2& vec2) const;
        void setVec3f(const std::string& name, const glm::vec3& vec3) const;
        void setVec4f(const std::string& name, const glm::vec4& vec4) const;
        void setMat4f(const std::string& name, const glm::mat4& mat4) const;
        void setBool(const std::string& name, bool in_bool) const;

    private:
        void CreateShaderProgram(GLuint fragment_shader, GLuint vertex_shader);
        GLuint CompilingShader(GLenum shader_type, const char* src);
        GLuint programID;
        bool is_init = false;
    };
}

#endif // !SHADER_H_

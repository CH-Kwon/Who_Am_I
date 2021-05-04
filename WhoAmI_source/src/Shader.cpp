/**
\file        Shader.cpp
\author      Sehyun Kim
\par         email: kim4969\@gmail.com
\par         course: GAM200
\date        11/22/2017.
\brief
All content (c) 2017 DigiPen (USA) Corporation, all rights reserved.
*/

#include "Shader.h"

#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <vector>

namespace FindersEngine
{
    GLuint Shader::CompilingShader(GLenum shader_type, const char* src)
    {
        GLint success;
        int info_log_length;
        GLuint shader = glCreateShader(shader_type);
        glShaderSource(shader, 1 /*one file*/, &src, NULL);
        glCompileShader(shader);
        // print compile errors
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        if (!success)
        {
            std::vector<char> info_log(info_log_length + 1);
            glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, NULL, info_log.data());
            if (shader_type == GL_VERTEX_SHADER)
            {
                std::cerr << "Error: Shader_Vertex_Compile_Failed\n"
                          << &info_log.front() << std::endl;
            }
            else if (shader_type == GL_FRAGMENT_SHADER)
            {
                std::cerr << "Error: Shader_Fragment_Compile_failed\n"
                          << &info_log.front() << std::endl;
            }
            else
            {
                std::cerr << "Error: Shader_Compile_failed\n"
                          << "Could you check your GLenum shader_type when calling CreateShader?\n"
                          << &info_log.front() << std::endl;
            }
        }
        return shader;
    }

    void Shader::CreateShaderProgram(GLuint vertex_shader, GLuint fragment_shader)
    {
        GLint success;
        int info_log_length;
        programID = glCreateProgram();
        glAttachShader(programID, vertex_shader);
        glAttachShader(programID, fragment_shader);
        glLinkProgram(programID);
        //repornt linking errors
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &info_log_length);
        if (!success)
        {
            std::vector<char> info_log(info_log_length + 1);
            glGetProgramInfoLog(programID, info_log_length, NULL, info_log.data());
            std::cerr << "Error: Shader_Program_Linking_Failed\n"
                      << &info_log.front() << std::endl;
        }
    }

    void Shader::init(const GLchar* vertex_path, const GLchar* fragment_path)

    {
        // vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        try
        {
            vShaderFile.open(vertex_path);
            fShaderFile.open(fragment_path);

            if (!vShaderFile.is_open())
            {
                std::cerr << "Error: The vertex shader file not found!" << std::endl;
            }
            if (!fShaderFile.is_open())
            {
                std::cerr << "Error: The fragment shader file not found!" << std::endl;
            }

            std::stringstream vShaderStream, fShaderStream;

            // read two buffers of files through stream
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            //close file(already copied)
            vShaderFile.close();
            fShaderFile.close();

            //converting stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cerr << "Error : Shader file could not successfuly read!" << std::endl;
        }
        catch (...)
        {
            std::cerr << "Error : Shader class construction, unknown some problems..." << std::endl;
        }

        const char* vertex_shader_code = vertexCode.c_str();
        const char* fragment_shader_code = fragmentCode.c_str();

        //two shader: vertex shader, fragment shader
        GLuint vertexShader, fragmentShader;

        //compiling vertex shader
        vertexShader = CompilingShader(GL_VERTEX_SHADER, vertex_shader_code);

        //compiling fragment shader
        fragmentShader = CompilingShader(GL_FRAGMENT_SHADER, fragment_shader_code);

        //Crate a Shader Program in ProgramID
        CreateShaderProgram(vertexShader, fragmentShader);

        // Delete the shaders, these are no longer to compile, because it already compiled and linked!
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        is_init = true;
    }

    void Shader::draw_begin()
    {
        assert(is_init && "Shader should init first!");
        // Start rendering
        glUseProgram(programID);
    }

    void Shader::draw_end() { glUseProgram(NULL); }

    void Shader::setFloat(const std::string& name, GLfloat value) const { glUniform1f(glGetUniformLocation(programID, name.c_str()), value); }
    void Shader::setInt(const std::string& name, GLuint value) const { glUniform1i(glGetUniformLocation(programID, name.c_str()), value); }
    void Shader::setVec2f(const std::string& name, const glm::vec2& vec2) const { glUniform2f(glGetUniformLocation(programID, name.c_str()), vec2.x, vec2.y); }
    void Shader::setVec3f(const std::string& name, const glm::vec3& vec3) const { glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(vec3)); }
    void Shader::setVec4f(const std::string& name, const glm::vec4& vec4) const { glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(vec4)); }
    void Shader::setMat4f(const std::string& name, const glm::mat4& mat4) const { glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4)); }
    void Shader::setBool(const std::string& name, bool in_bool) const { glUniform1i(glGetUniformLocation(programID, name.c_str()), in_bool); }
};

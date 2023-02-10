#include <vector>
#include "Shader.h"
#include <string>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#define GLFW_INCLUDE_ES3
#include "GLFW/glfw3.h"
#else
#include "glad/glad.h"
#endif


Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    // Creating a vertex shader
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    // Converting a shader to static char array
    const GLchar* source = vertexShaderSource.c_str();

    // Sending shader source to OpenGL
    glShaderSource(vertexShaderId, 1, &source, 0);

    // Compiling vertex shader
    glCompileShader(vertexShaderId);

    // Check if vertex shader compiled correctly
    GLint isCompiled = 0;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        // Reserve enough memory for info log
        GLint maxLength = 0;
        glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);

        // Putting GL info log message into char vector
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &infoLog[0]);

        // Shader can now be deleted
        glDeleteShader(vertexShaderId);

        return;
    }

    // Creating a fragment shader
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Converting a shader to static char array
    source = fragmentShaderSource.c_str();

    // Sending shader source to OpenGL
    glShaderSource(fragmentShaderId, 1, &source, 0);

    // Compiling vertex shader
    glCompileShader(fragmentShaderId);

    // Check if fragment shader compiled correctly
    isCompiled = 0;
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        // Reserve enough memory for info log
        GLint maxLength = 0;
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

        // Putting GL info log message into char vector
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &infoLog[0]);

        // Shader can now be deleted
        glDeleteShader(fragmentShaderId);

        return;
    }

    // Creating a shader program
    m_ProgramId = glCreateProgram();

    // Attaching shaders to our program
    glAttachShader(m_ProgramId, vertexShaderId);
    glAttachShader(m_ProgramId, fragmentShaderId);

    // Linking shaders in program
    glLinkProgram(m_ProgramId);

    // Checking if shaders linked correctly
    GLint isLinked = 0;
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        // Reserve enough memory for info log
        GLint maxLength = 0;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &maxLength);

        // Putting GL info log message into char vector
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(m_ProgramId, maxLength, &maxLength, &infoLog[0]);

        // Program can now be deleted
        glDeleteProgram(m_ProgramId);
        // Shader can now be deleted too
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);


        return;
    }

    // Shaders get detached after successful link
    glDetachShader(m_ProgramId, vertexShaderId);
    glDetachShader(m_ProgramId, fragmentShaderId);



}
Shader::~Shader()
{
    glDeleteProgram(m_ProgramId);
}

void Shader::bind() const
{
    glUseProgram(m_ProgramId);
    std::cout << "Binding shader \n";
}
void Shader::unbind() const
{
    glUseProgram(0);
}
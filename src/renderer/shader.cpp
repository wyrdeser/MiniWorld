#include "shader.h"

#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace 
{
std::string ReadFile(const std::string& path){
    std::ifstream file(path);

    if(!file.is_open()){
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int shader = glCreateShader(type);

    const char* sourceCode = source.c_str();

    glShaderSource(shader, 1, &sourceCode, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        char infoLog[512];

        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

        glDeleteShader(shader);

        throw std::runtime_error(std::string("Shader comilation failed: ") + infoLog);
    }

    return shader;
}
};

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath){
    std::string vertexSource = ReadFile(vertexPath);
    std::string fragmentSource = ReadFile(fragmentPath);

    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);

    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    mRendererID = glCreateProgram();

    glAttachShader(mRendererID, vertexShader);
    glAttachShader(mRendererID, fragmentShader);

    glLinkProgram(mRendererID);

    int success = 0;
    glGetProgramiv(mRendererID, GL_LINK_STATUS, &success);

    if(!success){
        char infoLog[512];

        glGetProgramInfoLog(mRendererID, sizeof(infoLog), nullptr, infoLog);

        glDeleteProgram(mRendererID);
        mRendererID = 0;

        throw std::runtime_error(std::string("Shader linking failed: ") + infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader(){
    if(mRendererID != 0){
        glDeleteProgram(mRendererID);
    }
}

void Shader::Use() const{
    glUseProgram(mRendererID);
}

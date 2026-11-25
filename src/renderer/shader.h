#pragma once

#include <string>

class Shader{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentShader);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void Use() const;

private:
    unsigned int mRendererID = 0;
};

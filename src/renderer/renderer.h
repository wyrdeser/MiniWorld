#pragma once
#include <memory>
#include "shader.h"

class Renderer {
public:
    bool Initialize();

    void BeginFrame(int width, int height);
    void Render();
    void EndFrame();
    void Shutdow();

private:
    std::unique_ptr<Shader> mBasicShader;

    unsigned int mVBO = 0;
    unsigned int mVAO = 0;
};

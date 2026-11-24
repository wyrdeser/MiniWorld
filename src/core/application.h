#pragma once

#include "window.h"
#include "../renderer/renderer.h"

class Application{
public:
    bool Initialize();
    void Run();
    void Shutdow();

private:
    void Update(float deltaTime);
    void Render();

private:
    Window window_;
    Renderer renderer_;

    bool running_ = false;
};

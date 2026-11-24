#pragma once

class Renderer {
public:
    bool Initialize();

    void BeginFrame(int width, int height);
    void Render();
    void EndFrame();
};

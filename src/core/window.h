#pragma once

#include <SDL3/SDL.h>

class Window{
public:
    Window() = default;
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool WindowInit(const char* title, int width, int height);
    void Shutdow();
    bool PollEvents();
    void SwapBuffers();
    void GetDrawableSize(int& width, int& height) const;

private:
    SDL_Window* window_ = nullptr;
    SDL_GLContext context_ = nullptr;
    bool sdlInitialized_ = false;
};

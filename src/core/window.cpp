#include "window.h"

#include <iostream>

Window::~Window(){
    Shutdow();
}

bool Window::WindowInit(const char* title, int width, int height){
    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "SDL Init" << std::endl;
        
        sdlInitialized_ = true;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window_ = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!window_) {
            std::cout << "Faile to create window!" << std::endl;
            Shutdow();
            return false;
        }

        context_ = SDL_GL_CreateContext(window_);
        if (!context_) {
            std::cout << "Faile to create context!" << std::endl;
            Shutdow();
            return false;
        }

        if(!SDL_GL_MakeCurrent(window_, context_)){
            std::cout << "Faile make curretn OpenGL!" << std::endl;
            Shutdow();
            return false;
        }

        SDL_GL_SetSwapInterval(1);

        return true;
    }
    else {
        std::cout << "SDL initialisation failed!" << std::endl;
        return false;
    }
}

void Window::Shutdow(){
    if(window_){
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    if(context_){
        SDL_GL_DestroyContext(context_);
        context_ = nullptr;
    }
    if(sdlInitialized_){
        SDL_Quit();
        sdlInitialized_ = false;
    }
}

bool Window::PollEvents(){
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
    }

    return true;
}

void Window::SwapBuffers(){
    if (window_) {
        SDL_GL_SwapWindow(window_);
    }

    // to do: custom swapbuffer
}

void Window::GetDrawableSize(int &width, int &height) const {
    if (window_) {
        SDL_GetWindowSizeInPixels(window_, &width, &height);
    }
    else{
        width = 0;
        height = 0;
    }
}



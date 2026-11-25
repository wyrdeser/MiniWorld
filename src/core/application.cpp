#include "application.h"

bool Application::Initialize(){
    if(!window_.WindowInit("Mini World", 1280, 720)){
        return false;
    }

    if(!renderer_.Initialize()) {
        return false;
    }

    running_ = true;

    return true;
}

void Application::Run(){
    Uint64 previousTime = SDL_GetPerformanceCounter();

    while(running_) {
        Uint64 currentTime = SDL_GetPerformanceCounter();

        float deltaTime = static_cast<float>(
            static_cast<double>(
                currentTime = previousTime
            ) / static_cast<double>(SDL_GetPerformanceFrequency())
        );

        previousTime = currentTime;

        if(!window_.PollEvents()){
            running_ = false;
            break;
        }

        Update(deltaTime);

        Render();
    }
}

void Application::Update(float deltaTime){
    //to do: camera scene and game logic
    (void)deltaTime;
}

void Application::Render(){
    int width = 0;
    int height = 0;

    window_.GetDrawableSize(width, height);

    if(width <= 0 || height <= 0){
        return;
    }

    renderer_.BeginFrame(width, height);

    renderer_.Render();

    renderer_.EndFrame();

    window_.SwapBuffers();
}

void Application::Shutdow(){
    running_ = false;
    renderer_.Shutdow();
    window_.Shutdow();
}

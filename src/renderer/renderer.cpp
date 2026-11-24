#include "renderer.h"

#include <glad/gl.h>
#include <SDL3/SDL_main.h>
#include <iostream>

bool Renderer::Initialize(){
    if(!gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress))){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

void Renderer::BeginFrame(int width, int height){
    glViewport(0, 0, width, height);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(){
    // to do: draw 3D object
}

void Renderer::EndFrame(){
    // to do: post processing
}

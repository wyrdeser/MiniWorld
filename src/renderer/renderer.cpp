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
    
    mBasicShader = std::make_unique<Shader>(
        std::string(MINIWORLD_ASSET_DIR) + "/shaders/basic.vert",
        std::string(MINIWORLD_ASSET_DIR) + "/shaders/basic.frag"
    );

    std::cout << "Shader initialized successfully!" << std::endl;
    
    float vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
}

void Renderer::BeginFrame(int width, int height){
    glViewport(0, 0, width, height);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    mBasicShader->Use();

    glBindVertexArray(mVAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    // to do: draw 3D object
}

void Renderer::EndFrame(){
    // to do: post processing
}

void Renderer::Shutdow(){
    if(mVBO != 0){
        glDeleteBuffers(1, &mVBO);
        mVBO = 0;
    }

    if(mVAO != 0){
        glDeleteVertexArrays(1, &mVAO);
        mVAO = 0;
    }

    mBasicShader.reset();
}

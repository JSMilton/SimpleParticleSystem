//
//  GLRenderer.cpp
//  GyroSquares
//
//  Created by James Milton on 28/05/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "GLRenderer.h"

void GLRenderer::initOpenGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    mViewWidth = 1200;
    mViewHeight = 800;
    reshape(1200, 800);
    
    render(0.0);
}

void GLRenderer::render(float dt) {
    const float FPS_CLAMP = 1.0f / 15.0f;
    if (dt > FPS_CLAMP)
        dt = FPS_CLAMP;
    
    freeGLBindings();
    
    mPreviousViewMatrix = mViewMatrix;
}

void GLRenderer::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    mViewWidth = width;
    mViewHeight = height;
    mProjectionMatrix = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
    mViewMatrix = glm::lookAt(glm::vec3(0,0,20), glm::vec3(0,0,0), glm::vec3(0,1,0));
    
    createFrameBuffers();
}

int velMod = 1500;
void GLRenderer::leap_rightHandVelocity(float x, float y, float z) {
}

void GLRenderer::leap_leftHandVelocity(float x, float y, float z) {
}

void GLRenderer::freeGLBindings(void) const
{
    glBindFramebuffer(GL_FRAMEBUFFER,     0);
    glBindRenderbuffer(GL_RENDERBUFFER,   0);
    glBindBuffer(GL_ARRAY_BUFFER,         0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D,          0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,    0);
}

void GLRenderer::resetFramebuffers() {
}

void GLRenderer::createFrameBuffers() {
    resetFramebuffers();
}
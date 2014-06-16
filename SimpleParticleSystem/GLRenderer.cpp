//
//  GLRenderer.cpp
//  GyroSquares
//
//  Created by James Milton on 28/05/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "GLRenderer.h"
#include "SimpleParticleModel.h"
#include "SimpleParticleShader.h"
#include "SimpleParticleFeedbackShader.h"
#include "ImageLoader.h"
#include "ObjModelLoader.h"

void GLRenderer::initOpenGL() {
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    mViewWidth = 1200;
    mViewHeight = 800;
    reshape(1200, 800);
    
    mSimpleParticleModel = new SimpleParticleModel;
    mSimpleParticleShader = new SimpleParticleShader;
    mSimpleParticleFeedbackShader = new SimpleParticleFeedbackShader;
    
    mParticleModelA = new SimpleParticleModel;
    mParticleModelB = new SimpleParticleModel;
    mParticleModelC = new SimpleParticleModel;
    mParticleModelD = new SimpleParticleModel;
    
    lightPosition = glm::vec3(0.0,10.0,10.0);
    
    ImageLoader *myImage = new ImageLoader("Droplet");
    glGenTextures(1, &mParticleTexture);
    glBindTexture(GL_TEXTURE_2D, mParticleTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 (GLint)myImage->mWidth, (GLint)myImage->mHeight, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, static_cast<const GLvoid*>(myImage->mImageData));
    
    myImage->~ImageLoader();
    delete myImage;
    
    emitterPosition = glm::vec3(0.5,0,0);
    emitterPosition2 = glm::vec3(-0.5,0,0);
    
    mBuffer = 0;
    
    glEnable (GL_PROGRAM_POINT_SIZE);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ObjModelLoader *myObj = new ObjModelLoader("cross", false);
    
    render(0.0);
}

void GLRenderer::render(float dt) {
    const float FPS_CLAMP = 1.0f / 15.0f;
    if (dt > FPS_CLAMP)
        dt = FPS_CLAMP;
    
    freeGLBindings();
    
    mSimpleParticleFeedbackShader->enable();
    glUniform3fv(mSimpleParticleFeedbackShader->mEmitterPositionHandle, 1, glm::value_ptr(emitterPosition));
    glUniform1f(mSimpleParticleFeedbackShader->mElapsedTimeHandle, timer += (GLfloat)dt);
    
    if (mBuffer == 0){
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mParticleModelA->mVBO);
    } else {
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mParticleModelB->mVBO);
    }
    
    glEnable(GL_RASTERIZER_DISCARD);
    
    // perform transform feedback
    glBeginTransformFeedback(GL_POINTS);
    if (mBuffer == 0){
        mParticleModelB->drawArrays();
    } else {
       mParticleModelA->drawArrays();
    }
    glEndTransformFeedback();
    
    glUniform3fv(mSimpleParticleFeedbackShader->mEmitterPositionHandle, 1, glm::value_ptr(emitterPosition2));
    if (mBuffer == 0){
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mParticleModelC->mVBO);
    } else {
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, mParticleModelD->mVBO);
    }
    glBeginTransformFeedback(GL_POINTS);
    if (mBuffer == 0){
        mParticleModelD->drawArrays();
    } else {
        mParticleModelC->drawArrays();
    }
    glEndTransformFeedback();

    
    glDisable(GL_RASTERIZER_DISCARD);
    
    mSimpleParticleFeedbackShader->disable();
    
    /* Render Particles. Enabling point re-sizing in vertex shader */
    
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mSimpleParticleShader->enable();
    /* update time in shaders */
    glUniformMatrix4fv(mSimpleParticleShader->mProjectionMatrixHandle, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
    glUniformMatrix4fv(mSimpleParticleShader->mViewMatrixHandle, 1, GL_FALSE, glm::value_ptr(mViewMatrix));
    glUniform3fv(mSimpleParticleShader->mLightPositionWorldHandle, 1, glm::value_ptr(lightPosition));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mParticleTexture);
    glUniform1i(mSimpleParticleShader->mTextureHandle, 0);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    if (mBuffer == 0){
        mParticleModelA->drawArrays();
        mParticleModelC->drawArrays();
    } else {
        mParticleModelB->drawArrays();
        mParticleModelD->drawArrays();
    }
    mSimpleParticleShader->disable();
    
    mPreviousViewMatrix = mViewMatrix;
    
    emitterPosition = glm::rotateY(emitterPosition, mParticleRotationVelocity);
    emitterPosition2.x = emitterPosition.x * -1;
    emitterPosition2.y = emitterPosition.y * -1;
    emitterPosition2.z = emitterPosition.z * -1;
    
    mBuffer++;
    if (mBuffer > 1)mBuffer = 0;
    
    mParticleRotationVelocity *= 0.99;
}

void GLRenderer::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    mViewWidth = width;
    mViewHeight = height;
    mProjectionMatrix = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);
    mViewMatrix = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    
    createFrameBuffers();
}

int velMod = 5000;

void GLRenderer::leap_velocity(float x, float y, float z) {
    
//    if(lightPosition.x < 50 && lightPosition.x > -50){
//        lightPosition.x += x/1000;
//    }
//    
//    if(lightPosition.y < 50 && lightPosition.y > -50){
//        lightPosition.y += y/1000;
//    }
//    
//    if(lightPosition.z < 50 && lightPosition.z > -50){
//        lightPosition.z += z/1000;
//    }
}

void GLRenderer::leap_rightHandVelocity(float x, float y, float z) {
    //timer += x / velMod;
}

void GLRenderer::leap_leftHandVelocity(float x, float y, float z) {
}

// values are normalised
void GLRenderer::leap_position(float x, float y, float z) {
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

void GLRenderer::moveLightSourceByNormalisedVector(float x, float y, float z) {
    float range = 2;
    lightPosition.x = (range * x) - (range / 2);
    lightPosition.y = (range * y) - (range / 2);
    lightPosition.z = (range * z) - (range / 2);
}

void GLRenderer::changeParticleVelocity(float velocity) {
    //timer += velocity / velMod;
    mParticleRotationVelocity += velocity / 3000;
//    emitterPosition = glm::rotateY(emitterPosition, velocity/10);
//    emitterPosition2.x = emitterPosition.x * -1;
//    emitterPosition2.y = emitterPosition.y * -1;
//    emitterPosition2.z = emitterPosition.z * -1;
}

void GLRenderer::resetFramebuffers() {
}

void GLRenderer::createFrameBuffers() {
    resetFramebuffers();
}
//
//  GLRenderer.h
//  GyroSquares
//
//  Created by James Milton on 28/05/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glUtil.h"

class SimpleParticleModel;
class SimpleParticleShader;

class GLRenderer {
public:
    void initOpenGL();
    void render(float dt);
    void reshape(int width, int height);
    void destroy();
    void leap_rightHandVelocity(float x, float y, float z);
    void leap_leftHandVelocity(float x, float y, float z);
    
private:
    void createFrameBuffers();
    void resetFramebuffers();
    void freeGLBindings() const;
    
    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mPreviousViewMatrix;
    
    int mViewWidth;
    int mViewHeight;
    
    SimpleParticleModel *mSimpleParticleModel;
    SimpleParticleShader *mSimpleParticleShader;
};

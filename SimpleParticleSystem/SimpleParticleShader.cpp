//
//  SimpleParticleShader.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 04/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "SimpleParticleShader.h"

SimpleParticleShader::SimpleParticleShader() : BaseShader("simpleParticle", "simpleParticle") {
    linkProgram();
    mProjectionMatrixHandle = getUniformLocation("uProjectionMatrix");
    mViewMatrixHandle = getUniformLocation("uViewMatrix");
    mLightPositionWorldHandle = getUniformLocation("uLightPositionWorld");
    mTextureHandle = getUniformLocation("tex");
}
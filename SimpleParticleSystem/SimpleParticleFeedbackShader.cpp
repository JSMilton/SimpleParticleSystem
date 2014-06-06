//
//  SimpleParticleFeedbackShader.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 06/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "SimpleParticleFeedbackShader.h"

SimpleParticleFeedbackShader::SimpleParticleFeedbackShader() : BaseShader("simpleParticleFeedback", NULL) {
    
    // specify transform feedback output
    const char *varyings[] = {"outPosition", "outVelocity", "outStartTime", "outOpacity"};
    glTransformFeedbackVaryings(mProgram, 4, varyings, GL_INTERLEAVED_ATTRIBS);
    linkProgram();
    
    mEmitterPositionHandle = getUniformLocation("uEmitterPosition");
    mElapsedTimeHandle = getUniformLocation("uElapsedTime");
}
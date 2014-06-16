//
//  SimpleParticleFeedbackShader.h
//  SimpleParticleSystem
//
//  Created by James Milton on 06/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "BaseShader.h"

class SimpleParticleFeedbackShader : public BaseShader {
public:
    SimpleParticleFeedbackShader();
    
    GLint mEmitterPositionHandle;
    GLint mElapsedTimeHandle;
    GLint mModelMatrixHandle;
};

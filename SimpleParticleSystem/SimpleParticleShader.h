//
//  SimpleParticleShader.h
//  SimpleParticleSystem
//
//  Created by James Milton on 04/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "BaseShader.h"

class SimpleParticleShader : public BaseShader {
public:
    SimpleParticleShader();
    GLint mViewMatrixHandle;
    GLint mProjectionMatrixHandle;
    GLint mEmitterPositionHandle;
    GLint mElapsedTimeHandle;
    GLint mLightPositionWorldHandle;
    GLint mTextureHandle;
};

//
//  ObjModelLoader.h
//  SimpleParticleSystem
//
//  Created by James Milton on 11/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#ifndef __SimpleParticleSystem__ObjModelLoader__
#define __SimpleParticleSystem__ObjModelLoader__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glUtil.h"

class ObjModelLoader {
public:
    ObjModelLoader(const char* objFileName);
    ~ObjModelLoader();
    
    GLubyte *mPositions;
    GLenum mPositionType;
    GLuint mPositionSize;
    GLsizei mPositionArraySize;
    
    GLubyte *mColors;
    GLenum mColorType;
    GLuint mColorSize;
    GLsizei mColorArraySize;
    
    GLubyte *mNormals;
    GLenum mNormalType;
    GLuint mNormalSize;
    GLsizei mNormalArraySize;
    
    GLubyte *mTextureUV;
    GLenum mTextureType;
    GLuint mTextureSize;
    GLsizei mTexureUVArraySize;
};

#endif /* defined(__SimpleParticleSystem__ObjModelLoader__) */

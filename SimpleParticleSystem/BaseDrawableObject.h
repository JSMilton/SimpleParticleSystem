//
//  BaseDrawableObject.h
//  SimpleParticleSystem
//
//  Created by James Milton on 04/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#ifndef BASEDRAWABLEOBJECT_H
#define BASEDRAWABLEOBJECT_H

#include <iostream>
#include "glUtil.h"

class BaseDrawableObject {
public:
    BaseDrawableObject();
    void drawElements();
    void drawArrays();
    
protected:
    GLuint mVAO;
    GLuint mNumVertices;
    GLenum mPrimitiveType;
    GLubyte *mElements;
	GLenum mElementType;
	GLuint mNumElements;
	GLsizei mElementArraySize;
};

#endif // _BaseDrawableObject__H

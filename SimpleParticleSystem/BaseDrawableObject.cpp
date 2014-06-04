//
//  BaseDrawableObject.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 04/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "BaseDrawableObject.h"

BaseDrawableObject::BaseDrawableObject() {
    mVAO = 0;
    mNumVertices = 0;
    mPrimitiveType = GL_TRIANGLES;
    mElementType = GL_FLOAT;
    mElementArraySize = 0;
    mElements = NULL;
    mNumElements = 0;
}

void BaseDrawableObject::drawElements() {
    glBindVertexArray(mVAO);
    glDrawElements(mPrimitiveType, mNumElements, mElementType, 0);
    glBindVertexArray(0);
}

void BaseDrawableObject::drawArrays() {
    glBindVertexArray(mVAO);
    glDrawArrays(mPrimitiveType, 0, mNumVertices);
    glBindVertexArray(0);
}
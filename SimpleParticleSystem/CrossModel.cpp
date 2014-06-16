//
//  CrossModel.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 16/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "CrossModel.h"
#include "ObjModelLoader.h"

CrossModel::CrossModel() : BaseModel() {
    ObjModelLoader crossObj = ObjModelLoader("thinLine", false);
    mPositions = crossObj.mPositions;
    mPositionArraySize = crossObj.mPositionArraySize;
    mPositionSize = crossObj.mPositionSize;
    mPositionType = crossObj.mPositionType;
    
    mNormals = crossObj.mNormals;
    mNormalArraySize = crossObj.mNormalArraySize;
    mNormalSize = crossObj.mNormalSize;
    mNormalType = crossObj.mNormalType;
    
    mNumVertices = crossObj.mNumVertices;
    
    buildVAO();
}

void CrossModel::update(GLint modelMatrixHandle) {
    mVelocityVector.x *= 0.99;
    mVelocityVector.y *= 0.99;
    mVelocityVector.z *= 0.99;
    
    rotateModelByVector3AndAngle(1, 0, 0, mVelocityVector.x);
    rotateModelByVector3AndAngle(0, 1, 0, mVelocityVector.y);
    
    glm::mat4 modelMatrix = BaseModel::createModelMatrix();
    
    glUniformMatrix4fv(modelMatrixHandle, 1, GL_FALSE, glm::value_ptr(BaseModel::createModelMatrix()));
    
    mPreviousModelMatrix = modelMatrix;
}

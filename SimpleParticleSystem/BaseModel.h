//
//  BaseModel.h
//  GyroSquares
//
//  Created by James Milton on 29/05/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include "BaseDrawableObject.h"
#include <string.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum {
    POSITION_ATTRIB_IDX,
    NORMAL_ATTRIB_IDX,
    TEXTURE_ATTRIB_IDX,
    COLOR_ATTRIB_IDX
};

class BaseModel : public BaseDrawableObject {
public:
    BaseModel();
    ~BaseModel();
    void loadObjectFile(const char* objFile);
    void buildVAO();
    void translateModelByVector3(float x, float y, float z);
    void rotateModelByVector3AndAngle(float x, float y, float z, float angle);
    void scaleModelByVector3(float x, float y, float z);
    glm::mat4 getPreviousModelMatrix();
    glm::mat4 getModelMatrix();
    
protected:
    glm::mat4 createModelMatrix();
	
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
    
    glm::mat4 mRotationMatrix;
    glm::mat4 mScaleMatrix;
    glm::mat4 mTranslationMatrix;
    glm::mat4 mPreviousModelMatrix;
};

#endif // BASE_MODEL_H
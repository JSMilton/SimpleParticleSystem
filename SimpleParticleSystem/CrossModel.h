//
//  CrossModel.h
//  SimpleParticleSystem
//
//  Created by James Milton on 16/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "BaseModel.h"

class CrossModel : public BaseModel {
public:
    CrossModel();
    
    void update(GLint modelMatrixHandle);
    
    glm::mat4 mPreviousModelMatrix;
    glm::vec3 mVelocityVector;
};

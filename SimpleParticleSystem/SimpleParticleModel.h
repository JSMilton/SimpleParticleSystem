//
//  SimpleParticleModel.h
//  SimpleParticleSystem
//
//  Created by James Milton on 04/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "BaseDrawableObject.h"
#include "glm/glm.hpp"

typedef struct {
    glm::vec3 position;
    glm::vec3 velocity;
    float startTime;
    float opacity;
}Particle;

class SimpleParticleModel : public BaseDrawableObject {
public:
    SimpleParticleModel();
    
    GLuint mVBO;
};

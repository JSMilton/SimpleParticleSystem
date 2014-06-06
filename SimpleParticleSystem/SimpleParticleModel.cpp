//
//  SimpleParticleModel.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 04/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "SimpleParticleModel.h"

#define PARTICLE_COUNT 10000 // tweak me to see if we need more/less particles

SimpleParticleModel::SimpleParticleModel() : BaseDrawableObject() {
    Particle particles[PARTICLE_COUNT];
    float t_accum = 0.0f; // start time
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        // start times
        particles[i].startTime = t_accum;
        t_accum += 0.01f; // spacing for start times is 0.01 seconds
        // start velocities. randomly vary x and z components
        float randx = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
        float randz = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
        particles[i].velocity.x = randx; // x
        particles[i].velocity.y = 1.0f; // y
        particles[i].velocity.z = randz; // z
        particles[i].position = glm::vec3(0,0,0);
        particles[i].opacity = 0.0;
    }
    
    glGenBuffers (1, &mVBO);
    glBindBuffer (GL_ARRAY_BUFFER, mVBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (particles), particles, GL_STATIC_DRAW);
    
    glGenVertexArrays (1, &mVAO);
    glBindVertexArray (mVAO);
    glBindBuffer (GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(GL_FLOAT) * 3));
    glVertexAttribPointer (2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(GL_FLOAT) * 6));
    glVertexAttribPointer (3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(GL_FLOAT) * 7));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    mNumVertices = PARTICLE_COUNT;
    mPrimitiveType = GL_POINTS;
}
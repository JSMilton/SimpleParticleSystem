//
//  SimpleParticleModel.cpp
//  SimpleParticleSystem
//
//  Created by James Milton on 04/06/2014.
//  Copyright (c) 2014 James Milton. All rights reserved.
//

#include "SimpleParticleModel.h"

#define PARTICLE_COUNT 1000 // tweak me to see if we need more/less particles

SimpleParticleModel::SimpleParticleModel() : BaseDrawableObject() {
    float vv[PARTICLE_COUNT * 3]; // start velocities vec3
    float vt[PARTICLE_COUNT]; // start times
    float t_accum = 0.0f; // start time
    int j = 0;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        // start times
        vt[i] = t_accum;
        t_accum += 0.01f; // spacing for start times is 0.01 seconds
        // start velocities. randomly vary x and z components
        float randx = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
        float randz = ((float)rand() / (float)RAND_MAX) * 1.0f - 0.5f;
        vv[j] = randx; // x
        vv[j + 1] = 1.0f; // y
        vv[j + 2] = randz; // z
        j+= 3;
    }
    
    GLuint velocity_vbo;
    glGenBuffers (1, &velocity_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, velocity_vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vv), vv, GL_STATIC_DRAW);
    
    GLuint time_vbo;
    glGenBuffers (1, &time_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, time_vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vt), vt, GL_STATIC_DRAW);
    
    glGenVertexArrays (1, &mVAO);
    glBindVertexArray (mVAO);
    glBindBuffer (GL_ARRAY_BUFFER, velocity_vbo);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer (GL_ARRAY_BUFFER, time_vbo);
    glVertexAttribPointer (1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    
    mNumVertices = PARTICLE_COUNT;
    mPrimitiveType = GL_POINTS;
}
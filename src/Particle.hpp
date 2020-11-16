//
//  Particle.hpp
//  mySketch
//
//  Created by Luiza Comanescu on 16/11/2020.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include <vector>

typedef struct Particle {
    float xColour = 99.0;
    float yColour = 58.0;
    float zColour = 20.0;
    
    float xPos;
    float yPos;
    float zPos;
    float radius;
    
    float xVel;
    float yVel;
    
    float mass;
} Particle;

extern std::vector<Particle> particleSystem;
extern void emitter();

#endif /* Particle_hpp */

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
#include "BlackHole.hpp"

typedef struct Particle {
    float xColour = 99.0;
    float yColour = 58.0;
    float zColour = 20.0;
    
    float xPos;
    float yPos;
    float zPos;
    
    float initX;
    float initY;
    
    
    float radius;
    float smallRadius = -10;
    
    float xVel;
    float yVel;
    
    float mass;
    bool hasReachedBlackHole = false;
    BlackHoles blackhole = BlackHoles();
    float rotationAngle = 0;
} Particle;

extern std::vector<Particle> particleSystem;
extern void emitter();

#endif /* Particle_hpp */

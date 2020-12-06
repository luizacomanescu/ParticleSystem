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
#define MAX_PARTICLES 100000

typedef struct Particle {
    float xColour = 99.0;
    float yColour = 58.0;
    float zColour = 20.0;
    
    float xPos;
    float yPos;
    float zPos;
    
    float xScale;
    float yScale;
    float zScale;
    
    float initX;
    float initY;
    
    
    float radius;
    float smallRadius = -10;
    
    float xVel;
    float yVel;
    
    float mass;
    bool hasReachedBlackHole = false;
    bool life = true;
    BlackHoles blackhole = BlackHoles();
    float rotationAngle = -0.1;
    
    bool turbulance = false;
} Particle;

extern std::vector<Particle> particleSystem;
extern void emitter();
extern bool checkCollison(int index);

#endif /* Particle_hpp */

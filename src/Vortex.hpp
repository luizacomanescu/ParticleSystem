//
//  Vortex.hpp
//  ParticleSystem
//
//  Created by Luiza Comanescu on 24/11/2020.
//

#ifndef Vortex_hpp
#define Vortex_hpp

#include <stdio.h>
#include <vector>

#endif /* Vortex_hpp */

typedef struct Vortex {
    float x = - 100;
    float y = - 300;
    float radius = 300;
    float speed = 15.5;
    float velx;
    float vely;
    float scale = 10;
    int lifetime;
} Vortex;

extern std::vector<Vortex> vortexes;
extern Vortex vortex;

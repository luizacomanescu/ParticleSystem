//
//  Particle.cpp
//  mySketch
//
//  Created by Luiza Comanescu on 16/11/2020.
//

#include "Particle.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "ofApp.h"
#include <iostream>


using namespace std;


int newAsteroids;
int noAsteroids = 300;
int intensity = 30;
float heaviness = -10.0;

int random(int min, int max);

vector<Particle> particleSystem;

void emitter(void)
{
    for (int asteroidIndex = particleSystem.size(); asteroidIndex < noAsteroids ; asteroidIndex++) {
            
        particleSystem.push_back(Particle());
        particleSystem[asteroidIndex].xPos = random(-1000.0,1000.0);
        particleSystem[asteroidIndex].yPos = random(- 900, 0);
        particleSystem[asteroidIndex].zPos = random(- 1000 / 10, 0) - 20;
        particleSystem[asteroidIndex].xScale = 0.07 * drand48();
        particleSystem[asteroidIndex].yScale = 0.07 * drand48();
        particleSystem[asteroidIndex].zScale = 0.07 * drand48();
        particleSystem[asteroidIndex].radius = random(7.0, 19.0);
        particleSystem[asteroidIndex].mass = - particleSystem[asteroidIndex].radius;
        
        if(particleSystem[0].turbulance)
            particleSystem[asteroidIndex].turbulance = true;
                
        int minimumDistance = INT_MAX;
        for(int blackHoleIndex = 0; blackHoleIndex < blackholes.size(); blackHoleIndex++)
        {
            if(particleSystem[asteroidIndex].radius * 2 >= blackholes[blackHoleIndex].radius)
            {
                continue;
            }
            else
            {
                float distance = sqrt(pow(particleSystem[asteroidIndex].xPos - blackholes[blackHoleIndex].x,2) + pow(particleSystem[asteroidIndex].yPos - blackholes[blackHoleIndex].y,2));
                
                if(distance < minimumDistance) {
                    minimumDistance = distance;
                    particleSystem[asteroidIndex].blackhole = blackholes[blackHoleIndex];
                }
            }
        }
        
        particleSystem[asteroidIndex].initX = particleSystem[asteroidIndex].blackhole.x;
        particleSystem[asteroidIndex].initY = particleSystem[asteroidIndex].blackhole.y;
        
    }
    
   // noAsteroids += particleSystem.size();
}

int random(int min, int max)
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) );
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}


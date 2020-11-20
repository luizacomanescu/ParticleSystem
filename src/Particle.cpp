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
#define MAX_PARTICLES 10

using namespace std;


int newAsteroids;
int noAsteroids;
int intensity = 30;
float heaviness = -10.0;

int random(int min, int max);

vector<Particle> particleSystem;

void emitter(void)
{
    for (int asteroidIndex = 0 ; asteroidIndex < MAX_PARTICLES ; asteroidIndex++) {
        particleSystem.push_back(Particle());
        particleSystem[asteroidIndex].xPos = 0.0;
        particleSystem[asteroidIndex].yPos = random(- SCREEN_HEIGHT, 0);
        particleSystem[asteroidIndex].zPos = random(- SCREEN_WIDTH / 10, 0);
        particleSystem[asteroidIndex].radius = random(9.0, 23.0);
        particleSystem[asteroidIndex].mass = -0.3 + heaviness * drand48();
        
        int minimumDistance = INT_MAX;
        for(int blackHoleIndex = 0; blackHoleIndex < blackholes.size(); blackHoleIndex++)
        {
            if(particleSystem[asteroidIndex].radius * 3 >= blackholes[blackHoleIndex].radius)
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
        
    }
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


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
    for (int i = 0 ; i < MAX_PARTICLES ; i++) {
        particleSystem.push_back(Particle());
        particleSystem[i].xPos = 0.0;
        particleSystem[i].yPos = random(- SCREEN_HEIGHT, 0);
        particleSystem[i].zPos = random(- SCREEN_WIDTH / 10, 0);
        particleSystem[i].radius = random(9.0, 23.0);
        particleSystem[i].mass = -0.3 + heaviness * drand48();
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


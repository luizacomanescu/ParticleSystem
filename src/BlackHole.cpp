//
//  BlackHole.cpp
//  mySketch
//
//  Created by Luiza Comanescu on 16/11/2020.
//

#include "BlackHole.hpp"
#include <vector>

using namespace std;

vector<BlackHoles> blackholes;


void evokeBlackHoles() {
    blackholes.push_back(BlackHoles());
    blackholes[0].x = - 25.0;
    blackholes[0].y = - 50.0;
    blackholes[0].radius = 24.0;
    blackholes[0].resy = 340.0;
    blackholes[0].mass = -24;
    
    blackholes.push_back(BlackHoles());
    blackholes[1].x = - 230.0;
    blackholes[1].y = - 230.0;
    blackholes[1].radius = 70;
    blackholes[0].resy = 520.0;
    blackholes[1].mass = -70;
    
    blackholes.push_back(BlackHoles());
    blackholes[2].x = - 450.0;
    blackholes[2].y = - 380.0;
    blackholes[2].radius = 90;
    blackholes[0].resy = 665.0;
    blackholes[2].mass = -90;
    
    blackholes.push_back(BlackHoles());
    blackholes[3].x = - 540.0;
    blackholes[3].y = - 20.0;
    blackholes[3].radius = 20.0;
    blackholes[0].resy = 310.0;
    blackholes[3].mass = -20;
    
    blackholes.push_back(BlackHoles());
    blackholes[4].x = - 100.0;
    blackholes[4].y = - 380.0;
    blackholes[4].radius = 70;
    blackholes[0].resy = 665.0;
    blackholes[4].mass = -78;
}

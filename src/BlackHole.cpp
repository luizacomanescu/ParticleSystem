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
    
    blackholes.push_back(BlackHoles());
    blackholes[1].x = - 100.0;
    blackholes[1].y = - 230.0;
    blackholes[1].radius = 45;
    
    blackholes.push_back(BlackHoles());
    blackholes[2].x = - 321.0;
    blackholes[2].y = - 380.0;
    blackholes[2].radius = 78;
    
    blackholes.push_back(BlackHoles());
    blackholes[3].x = - 540.0;
    blackholes[3].y = - 20.0;
    blackholes[3].radius = 10.0;
}

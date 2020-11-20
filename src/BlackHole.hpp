//
//  BlackHole.hpp
//  mySketch
//
//  Created by Luiza Comanescu on 16/11/2020.
//

#ifndef BlackHole_hpp
#define BlackHole_hpp

#include <stdio.h>
#include <vector>

typedef struct BlackHoles {
    float x;
    float y;
    float radius;
    float mass;
} BlackHoles;

extern std::vector<BlackHoles> blackholes;
extern void evokeBlackHoles();

#endif /* BlackHole_hpp */

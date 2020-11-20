#include "ofApp.h"
#include "BlackHole.hpp"
#include "Particle.hpp"
#include <math.h>

float gravity = 0.0010;
float theta;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape( SCREEN_WIDTH, SCREEN_HEIGHT );
    ofSetFrameRate( FRAME_RATE );
    ofBackground( ofColor::white );
    evokeBlackHoles();
    emitter();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++)
    {
//        if(particleSystem[asteroidIndex].hasReachedBlackHole)
//            continue;
        
        if(particleSystem[asteroidIndex].radius < 0)
            continue;
        
        float distance = sqrt(pow(particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x,2) + pow(particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y,2));
        
        if(distance <= particleSystem[asteroidIndex].blackhole.radius + particleSystem[asteroidIndex].radius) {
            if( particleSystem[asteroidIndex].rotationAngle == -360)
                continue;
            
            //particleSystem[asteroidIndex].rotationAngle ++;
            
            /**
             x1 = init_x + SMALL_RADIUS * cos(particleSystem[asteroidIndex].rotationAngle);
             y1 = init_y + SMALL_RADIUS * sin(particleSystem[asteroidIndex].rotationAngle);
             */
            
//            particleSystem[asteroidIndex].xPos = particleSystem[asteroidIndex].blackhole.x + particleSystem[asteroidIndex].smallRadius * cos(particleSystem[asteroidIndex].rotationAngle);
//            particleSystem[asteroidIndex].yPos = particleSystem[asteroidIndex].blackhole.y + particleSystem[asteroidIndex].smallRadius * sin(particleSystem[asteroidIndex].rotationAngle);
            
            particleSystem[asteroidIndex].xPos = cos(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x) - sin(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y) + particleSystem[asteroidIndex].blackhole.x;

            particleSystem[asteroidIndex].yPos = sin(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x) + cos(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y) + particleSystem[asteroidIndex].blackhole.y;
            
           // particleSystem[asteroidIndex].xPos ++;
            particleSystem[asteroidIndex].radius -= 0.1;
            particleSystem[asteroidIndex].rotationAngle -= 0.001;
            //particleSystem[asteroidIndex].smallRadius -= 1;
            
        }
        
        particleSystem[asteroidIndex].xVel += gravity * particleSystem[asteroidIndex].mass * particleSystem[asteroidIndex].blackhole.mass / distance;
        particleSystem[asteroidIndex].xPos -= particleSystem[asteroidIndex].xVel;
        particleSystem[asteroidIndex].initX = particleSystem[asteroidIndex].xPos;
        if(particleSystem[asteroidIndex].blackhole.y > particleSystem[asteroidIndex].yPos)
            particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].xVel;
        else
            particleSystem[asteroidIndex].yPos -= particleSystem[asteroidIndex].xVel;
        particleSystem[asteroidIndex].initY = particleSystem[asteroidIndex].yPos;
        

        
        
//            if(abs(particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x) > 1 && abs(particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y) > 1) {
//                particleSystem[asteroidIndex].xVel += gravity * particleSystem[asteroidIndex].mass * particleSystem[asteroidIndex].blackhole.mass / distance;
//                particleSystem[asteroidIndex].xPos += particleSystem[asteroidIndex].xVel;
//                particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].xVel;
//            }
//            if(abs(particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x) > 1)
//            {
//                particleSystem[asteroidIndex].xVel += gravity * particleSystem[asteroidIndex].mass * particleSystem[asteroidIndex].blackhole.mass / distance;
//                particleSystem[asteroidIndex].xPos += particleSystem[asteroidIndex].xVel;
//            }
//            else if(abs(particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y) > 1)
//            {
//                particleSystem[asteroidIndex].xVel += gravity * particleSystem[asteroidIndex].mass * particleSystem[asteroidIndex].blackhole.mass / distance;
//                particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].xVel;
//            }
//
        
        if(asteroidIndex == 0){
            cout << "Asteroid " << asteroidIndex << endl;
            cout << "Black hole x: "  << particleSystem[asteroidIndex].blackhole.x << endl;
            cout << "Distance: " << distance << endl;
            cout << "Radius: " << particleSystem[asteroidIndex].blackhole.radius << endl; 
            cout << "Asteroid x: "  << particleSystem[asteroidIndex].xPos << endl;
            cout << "Asteroid y: "  << particleSystem[asteroidIndex].yPos << endl;
        }
//
//        if(abs(particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x) <= 1 && abs(particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y) <= 1) {
//            particleSystem[asteroidIndex].hasReachedBlackHole = true;
//        }
            
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    for(int blackHoleIndex = 0; blackHoleIndex < blackholes.size(); blackHoleIndex++) {
        ofSetColor(0,0,0);
        ofDrawCircle(blackholes[blackHoleIndex].x,  blackholes[blackHoleIndex].y, blackholes[blackHoleIndex].radius);
    }
    
    for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++) {
        ofSetColor(particleSystem[asteroidIndex].xColour, particleSystem[asteroidIndex].yColour, particleSystem[asteroidIndex].zColour);
        ofDrawSphere(particleSystem[asteroidIndex].xPos, particleSystem[asteroidIndex].yPos, particleSystem[asteroidIndex].zPos, particleSystem[asteroidIndex].radius);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#include "ofApp.h"
#include "BlackHole.hpp"
#include "Particle.hpp"

float gravity = 0.0010;

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
    for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++) {
        particleSystem[asteroidIndex].xVel += gravity * particleSystem[asteroidIndex].mass;
        particleSystem[asteroidIndex].xPos += particleSystem[asteroidIndex].xVel;
        particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].yVel;
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

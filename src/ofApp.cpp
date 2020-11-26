#include "ofApp.h"
#include "BlackHole.hpp"
#include "Particle.hpp"
#include "Vortex.hpp"
#include <math.h>

float gravity = 0.006;
float theta;
bool turbulance = false;
bool collision = false;

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

        bool collisionOccurred = false;
        if(collision) {
        for(int collisionIndex = 0; collisionIndex < asteroidIndex; collisionIndex ++) {

                float distance = sqrt(pow(particleSystem[asteroidIndex].xPos - particleSystem[collisionIndex].xPos,2) + pow(particleSystem[asteroidIndex].yPos - particleSystem[collisionIndex].yPos,2));
            
            float restLength =  particleSystem[asteroidIndex].radius + particleSystem[collisionIndex].radius;

            if(distance + 1 <= restLength) {
                collisionOccurred = true;
                float force = (distance - restLength) / (distance * (particleSystem[asteroidIndex].mass + particleSystem[collisionIndex].mass));

//                    float totatlVel = particleSystem[asteroidIndex].xVel + particleSystem[collisionIndex].xVel;
//
//                    float frictionLoss = 0.95;
//                    totatlVel *= frictionLoss;
//
//                    float massMe = pow(particleSystem[asteroidIndex].radius,2);
//                    float massHe = pow(particleSystem[collisionIndex].radius,2);
//
//                    float total = massMe + massHe;
//
//                    float amntHe = massHe / total;
//                    float amntMe = massMe / total;

                    /**
                     balls[i].vel += amntHe * ( (totalVelMag * 0.5 )  *  pDist.normalized() );
                     balls[k].vel += amntMe * ( (totalVelMag * 0.5  )  * -pDist.nor
                     */
                
                /**
                 if (a.isFree()) a.moveBy(deltaForce * a.getInvMass(), false);
                   if (b.isFree()) b.moveBy(deltaForce * -b.getInvMass(), false);
                 */
                    particleSystem[asteroidIndex].xVel += 0.01 * distance * force * particleSystem[asteroidIndex].mass;

                    particleSystem[collisionIndex].xVel += 0.01 * distance * force * -particleSystem[collisionIndex].mass;
                
//                particleSystem[asteroidIndex].xVel *= -1;
//                particleSystem[collisionIndex].xVel *=-1;

//                    float ammountOverlapped = (particleSystem[asteroidIndex].radius + particleSystem[collisionIndex].radius) - distance;
//
//                    float delta = abs(particleSystem[asteroidIndex].xPos - particleSystem[collisionIndex].xPos);
                
//                    particleSystem[asteroidIndex].xPos += particleSystem[asteroidIndex].xVel;
//                    particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].xVel;
//                    particleSystem[collisionIndex].xPos += particleSystem[collisionIndex].xVel;
//                    particleSystem[collisionIndex].yPos += particleSystem[collisionIndex].xVel;

                break;

                }
            }
            
        }
        
        /**
                         Erase Particle
         */
        if(particleSystem[asteroidIndex].radius < 0.1) {
            
            particleSystem.erase(particleSystem.begin() + asteroidIndex);
            continue;
        }
        
        float distance = sqrt(pow(particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x,2) + pow(particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y,2));
        
        /**
                        Blackhole death
         */
        if(distance < particleSystem[asteroidIndex].blackhole.radius + particleSystem[asteroidIndex].radius) {
            
            particleSystem[asteroidIndex].turbulance = false;
            
            particleSystem[asteroidIndex].xPos = cos(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x) - sin(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y) + particleSystem[asteroidIndex].blackhole.x;

            particleSystem[asteroidIndex].yPos = sin(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].xPos - particleSystem[asteroidIndex].blackhole.x) + cos(particleSystem[asteroidIndex].rotationAngle) * (particleSystem[asteroidIndex].yPos - particleSystem[asteroidIndex].blackhole.y) + particleSystem[asteroidIndex].blackhole.y;
            
            particleSystem[asteroidIndex].radius -= 0.09;
            
            continue;
            
        }
        /**
                            Vortex terror
         */
        if(particleSystem[asteroidIndex].turbulance) {
            
            float dx = particleSystem[asteroidIndex].xPos-vortex.x;
            float dy = particleSystem[asteroidIndex].yPos-vortex.y;
                
            float vx = - dy * vortex.speed;
            float vy = dx * vortex.speed;
                
            float factor = 1/(1+(dx*dx+dy*dy)/vortex.scale);
                
            particleSystem[asteroidIndex].xVel = (vx - particleSystem[asteroidIndex].xVel) * factor;
                
            particleSystem[asteroidIndex].yVel = (vy - particleSystem[asteroidIndex].yVel) * factor;
            
            particleSystem[asteroidIndex].xPos += particleSystem[asteroidIndex].xVel;
            particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].yVel;
            
            int minimumDistance = INT_MAX;
            for(int blackHoleIndex = 0; blackHoleIndex < blackholes.size(); blackHoleIndex++)
            {
                if(particleSystem[asteroidIndex].radius * 2 < blackholes[blackHoleIndex].radius)
                {
                   
                float distance = sqrt(pow(particleSystem[asteroidIndex].xPos - blackholes[blackHoleIndex].x,2) + pow(particleSystem[asteroidIndex].yPos - blackholes[blackHoleIndex].y,2));
                    
                    if(distance < minimumDistance) {
                        minimumDistance = distance;
                        particleSystem[asteroidIndex].blackhole = blackholes[blackHoleIndex];
                    }
                }
            }
                
                continue;
        }
        
        if(collisionOccurred) {
            particleSystem[asteroidIndex].xPos += particleSystem[asteroidIndex].xVel;
            particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].xVel;
            continue;
        }
        particleSystem[asteroidIndex].xVel += gravity * particleSystem[asteroidIndex].mass * particleSystem[asteroidIndex].blackhole.mass / distance;
        
        if(particleSystem[asteroidIndex].blackhole.x > particleSystem[asteroidIndex].xPos){
            particleSystem[asteroidIndex].xPos += particleSystem[asteroidIndex].xVel;
        }
        else {
            particleSystem[asteroidIndex].xPos -= particleSystem[asteroidIndex].xVel;
        }
       
        if(particleSystem[asteroidIndex].blackhole.y > particleSystem[asteroidIndex].yPos){
            particleSystem[asteroidIndex].yPos += particleSystem[asteroidIndex].xVel;
        }
        else {
            particleSystem[asteroidIndex].yPos -= particleSystem[asteroidIndex].xVel;
        }
        
        particleSystem[asteroidIndex].initX = particleSystem[asteroidIndex].xPos;
        particleSystem[asteroidIndex].initY = particleSystem[asteroidIndex].yPos;
        
    }
    
    if(particleSystem.size() < MAX_PARTICLES)
        emitter();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(SCREEN_WIDTH, SCREEN_HEIGHT);
    ofSetColor(12,67,9,23);
    ofDrawCircle(vortex.x, vortex.y, vortex.radius);
    
    for(int blackHoleIndex = 0; blackHoleIndex < blackholes.size(); blackHoleIndex++) {
        ofSetColor(0,0,0);
        ofDrawCircle(blackholes[blackHoleIndex].x,  blackholes[blackHoleIndex].y, blackholes[blackHoleIndex].radius);
    }
    
    for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++) {
        ofSetColor(particleSystem[asteroidIndex].xColour, particleSystem[asteroidIndex].yColour, particleSystem[asteroidIndex].zColour);
        ofFill();
        ofDrawSphere(particleSystem[asteroidIndex].xPos, particleSystem[asteroidIndex].yPos, particleSystem[asteroidIndex].zPos, particleSystem[asteroidIndex].radius);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 55) {
        for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++)
        particleSystem[asteroidIndex].turbulance = true;
    }
    if(key == 56) {
        for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++)
        particleSystem[asteroidIndex].turbulance = false;
    }
    
    if(key == 57) {
        collision = true;
    }
    
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



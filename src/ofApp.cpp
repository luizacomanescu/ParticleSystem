#include "ofApp.h"
#include "BlackHole.hpp"
#include "Particle.hpp"
#include "Vortex.hpp"
#include <math.h>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    
    gui.setup();
    gui.add(gravity.setup("gravity", 0.1, 0.1, 3.1));
    gui.add(noOfAsteroids.setup("asteroids", 100, 0, MAX_PARTICLES));
    gui.add(collisionIntensity.setup("intensity", 0.001, 0.001, 2));
    gui.add(collisionToggle.setup("collision", false));
    gui.add(turbulenceToggle.setup("turbulence", false));
    
    noAsteroids += noOfAsteroids;
    
    ofSetCircleResolution(50);
   
    cam.setGlobalPosition(519.218, 972.452, -240.295);
    cam.setGlobalOrientation(glm::quat(0.627076, -0.777579, -0.0290952, -0.0360783));
    
    ofSetWindowShape( SCREEN_WIDTH, SCREEN_HEIGHT );
    ofSetFrameRate( FRAME_RATE );
    
    ofDisableArbTex();
    ofLoadImage(particleTex,"/Users/luizacomanescu/Downloads/13302-2.jpg");
    
    blackholeShader.load("shadersGL3/blackhole");
    vortexShader.load("shadersGL3/vortex");
    
    evokeBlackHoles();
    emitter();
}

//--------------------------------------------------------------
void ofApp::update(){
    noAsteroids = noOfAsteroids;
    for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++)
    {
        
        bool collisionOccurred = false;
        if(collisionToggle) {
            for(int collisionIndex = 0; collisionIndex < asteroidIndex; collisionIndex ++) {

                float distance = sqrt(pow(particleSystem[asteroidIndex].xPos - particleSystem[collisionIndex].xPos,2) + pow(particleSystem[asteroidIndex].yPos - particleSystem[collisionIndex].yPos,2));
            
                float restLength =  particleSystem[asteroidIndex].radius + particleSystem[collisionIndex].radius;

                if(distance + 1 <= restLength) {
                    collisionOccurred = true;
                    float force = (distance - restLength) / (distance * (particleSystem[asteroidIndex].mass + particleSystem[collisionIndex].mass)) * collisionIntensity;

                    particleSystem[asteroidIndex].xVel += distance * force * particleSystem[asteroidIndex].mass;

                    particleSystem[collisionIndex].xVel += distance * force * -particleSystem[collisionIndex].mass;

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
            
            particleSystem[asteroidIndex].radius -= 0.08;
            
            continue;
            
        }
        /**
                            Vortex terror
         */
        if(turbulenceToggle) {
            
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
        particleSystem[asteroidIndex].xVel += gravity * particleSystem[asteroidIndex].mass * particleSystem[asteroidIndex].blackhole.mass / pow(distance,2);
        
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
        
    }
    
    if(particleSystem.size() < MAX_PARTICLES)
        emitter();
    
    cout << "Last frame time: " << ofGetLastFrameTime() << endl;
    cout << "Number of asteroids: " << particleSystem.size() << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackgroundGradient(ofColor::grey, ofColor::black);

    cam.begin();
    
    ofTranslate(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    /**
                    Vortex
     */
    vortexShader.begin();
    vortexShader.setUniform1f("u_time", ofGetElapsedTimef() * 0.1);
    vortexShader.setUniform1f("radius", vortex.radius);
    vortexShader.setUniform2f("u_resolution", 200, ofGetHeight() - 500);
    ofDrawCircle(vortex.x, vortex.y, vortex.radius);
    vortexShader.end();
    
    /**
                    Blackholes
     */
    for(int blackHoleIndex = 0; blackHoleIndex < blackholes.size(); blackHoleIndex++) {
        blackholeShader.begin();
        blackholeShader.setUniform1f("u_time", ofGetElapsedTimef());
        blackholeShader.setUniform1f("radius",400);
        blackholeShader.setUniform2f("u_resolution", ofGetWidth() -  abs(blackholes[blackHoleIndex].x), blackholes[blackHoleIndex].resy);
       ofDrawCircle(blackholes[blackHoleIndex].x, blackholes[blackHoleIndex].y, -20.0, blackholes[blackHoleIndex].radius);
    }
    blackholeShader.end();
   
    
    /**
                    Asteroids
     */
    for(int asteroidIndex = 0; asteroidIndex < particleSystem.size(); asteroidIndex ++) {
        ofSetColor(ofColor::lightGrey);
        particleTex.bind();
        ofDrawSphere(particleSystem[asteroidIndex].xPos, particleSystem[asteroidIndex].yPos, particleSystem[asteroidIndex].zPos, particleSystem[asteroidIndex].radius);
    }
    particleTex.unbind();
    
    cam.end();
    
    gui.draw();
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



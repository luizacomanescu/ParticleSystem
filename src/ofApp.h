#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "Particle.hpp"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAME_RATE 30
#define MIN_BH 3
#define MAX_BH 9

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
  
    ofTexture particleTex;
    
    ofShader blackholeShader;
    ofShader vortexShader;
    
    
    ofxPanel gui;
    ofxFloatSlider gravity;
    ofxFloatField noOfAsteroids;
    ofxFloatSlider collisionIntensity;
    ofxToggle collisionToggle;
    ofxToggle turbulenceToggle;
    
};

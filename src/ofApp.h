#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxTweenzor.h"
#include "ofxLayer.h"
#include "ofxPostGlitch.h"

#include "Utils.h"
#include "Constants.h"
#include "Globals.hpp"

#include "GUI.hpp"
#include "Deforming.hpp"

class ofApp : public ofBaseApp
{
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
		
private:
    
    void updateGlitch();
    
    GUI gui;
    
    ofxLayer::Manager lMgmt;
    Deforming* deforming;
    
    // glitch
    ofxPostGlitch glitch;
    int numMaxRunningGlitch;
    vector<ofxPostGlitchType> glitchCandidtates;
    vector<ofxPostGlitchType> curGlitch;
    float lastPushTime;
    float glitchIntensity;
};

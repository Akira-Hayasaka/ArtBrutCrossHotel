//
//  GUI.hpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2016/12/30.
//
//

#ifndef GUI_hpp
#define GUI_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxInkSim.h"

#include "Constants.h"
#include "Globals.h"

class GUI
{
public:
    
    void setup(ofPtr<UniformInfos> uniforms);
    void update();
    void draw();
    
    void toggleVisible() { bHide = !bHide; }
    void hide() { bHide = true; }
    void show() { bHide = false; }
    bool isVisible() { return !bHide; }
    void resetToDefault();
    
private:
    
    bool bHide;
    
    // drawing contourFinder settings
    ofxPanel drawingCFSetting;
    
    ofxPanel gui;
    ofXml settings;
    ofPtr<UniformInfos> uniforms;
};

#endif /* GUI_hpp */

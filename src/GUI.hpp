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
#include "Constants.h"
#include "Globals.hpp"

class GUI
{
public:
    
    void setup();
    void update();
    void draw();
    
    void toggleVisible() { bHide = !bHide; }
    void hide() { bHide = true; }
    void show() { bHide = false; }
    bool isVisible() { return !bHide; }
    
private:
    
    bool bHide;
    
    // drawing contourFinder settings
    ofxPanel drawingCFSetting;
};

#endif /* GUI_hpp */

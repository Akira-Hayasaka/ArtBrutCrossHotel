//
//  Ink.hpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2017/01/06.
//
//

#ifndef Ink_hpp
#define Ink_hpp

#include "ofMain.h"
#include "ofxInkSim.h"
#include "ofxTweenzor.h"

#include "Constants.h"
#include "Globals.hpp"
#include "Utils.h"

class Ink
{
public:
    void setup();
    void update();
    void stroke();
    void draw();
    void clear();
    void fadeOut();

    ofPtr<UniformInfos> getUniformInfo() { return inkSim.getUniformInfo(); }
    
private:
    
    void onEndFadeOut(float* arg);
    void judgeDrawable();
    
    enum STATE
    {
        DRAWABLE,
        FADING,
        DONEFADE
    };
    STATE state;
    
    ofxInkSim inkSim;
    ofFbo fbo;
    vector<ofTexture> brushes;
    vector<ofColor> colors;

    const int maxStroke = 30;
    const float strokeInterval = 1.0;
    int numStroke;
    float lastStrokeTime;
    float fadeOutTime;
    float fadeAlpha;
    ofColor c;
    
    int w;
    int h;
};

#endif /* Ink_hpp */

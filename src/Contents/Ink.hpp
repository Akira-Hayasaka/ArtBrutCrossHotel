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

class Ink
{
public:
    void setup();
    void update();
    void stroke();
    void draw();
    void clear();

    ofPtr<UniformInfos> getUniformInfo() { return inkSim.getUniformInfo(); }
    
private:
    
    ofxInkSim inkSim;
    ofFbo fbo;
    vector<ofTexture> brushes;
};

#endif /* Ink_hpp */

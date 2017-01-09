//
//  Globals.cpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2016/12/30.
//
//

#include "Globals.hpp"

namespace Globals
{
    float ELAPSED_TIME;
    vector<ofFbo> morphSequence;
    ofTexture testTex;
    
    ofEvent<void> fadeout;
    
    // params
    ofParameter<float> minArea, maxArea, threshold;
    ofParameter<bool> holes;
    ofParameter<float> micSensitivity;
}
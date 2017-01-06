//
//  Globals.hpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2016/12/30.
//
//

#ifndef Globals_hpp
#define Globals_hpp

#include "ofMain.h"

namespace Globals
{
    extern float ELAPSED_TIME;
    extern ofTexture testTex;    
    
    // params
    extern ofParameter<float> minArea, maxArea, threshold;
    extern ofParameter<bool> holes;
    extern ofParameter<float> micSensitivity;
}

#endif /* Globals_hpp */

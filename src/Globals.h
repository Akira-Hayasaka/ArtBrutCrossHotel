//
//  Globals.h
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2016/12/30.
//
//

#ifndef Globals_hpp
#define Globals_hpp

#include "ofMain.h"
#include "ofxPubSubOsc.h"

struct Proto
{
	using Ref = shared_ptr<Proto>;
	Proto();
	vector<float> v;
};

namespace Globals
{
    extern float ELAPSED_TIME;
	extern Proto::Ref proto;
    extern ofTexture testTex;
    
    extern ofEvent<void> fadeout;

	extern vector<ofFbo> morphSequence;
    
    // params
    extern ofParameter<float> minArea, maxArea, threshold;
    extern ofParameter<bool> holes;
    extern ofParameter<float> micSensitivity;
}

#endif /* Globals_hpp */

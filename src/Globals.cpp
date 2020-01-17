//
//  Globals.cpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2016/12/30.
//
//

#include "Globals.h"

Proto::Proto()
{
	v.resize(10);
	ofxSubscribeOsc(13000, "/proto_values", v);

}
namespace Globals
{
    float ELAPSED_TIME;
	Proto::Ref proto;
    vector<ofFbo> morphSequence;
    ofTexture testTex;
    
    ofEvent<void> fadeout;
    
    // params
    ofParameter<float> minArea, maxArea, threshold;
    ofParameter<bool> holes;
    ofParameter<float> micSensitivity;
}
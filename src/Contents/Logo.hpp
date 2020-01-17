//
//  Logo.hpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2017/01/06.
//
//

#ifndef Logo_hpp
#define Logo_hpp

#include "ofMain.h"
#include "Globals.h"

class Logo
{
public:
    
    void setup();
    void update();
    void draw();
    
private:
    
    ofTrueTypeFont fontBig;
    ofTrueTypeFont fontSmall;

};

#endif /* Logo_hpp */

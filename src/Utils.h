//
//  Utils.h
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2016/12/30.
//
//

#ifndef Utils_h
#define Utils_h

#include "ofMain.h"

static bool isImgFile(string ext)
{
    if (ext == "jpg" || ext == "JPG" ||
        ext == "png" || ext == "PNG")
    {
        return true;
    }
    else
        return false;
}

static ofPoint getCircularRdmPos(float pRadius, ofPoint orig, bool bUniDist = false)
{
    float angle = ofRandomuf() * PI * 2;
    
    float radius = 0.0;
    if (bUniDist)
    {
        radius = sqrt(ofRandomuf()) * pRadius;
    }
    else
    {
        radius = ofRandomuf() * pRadius;
    }
    
    float x = orig.x + radius * cos(angle);
    float y = orig.y + radius * sin(angle);
    return ofPoint(x, y);
}

#endif /* Utils_h */

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

#endif /* Utils_h */

//
//  Logo.cpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2017/01/06.
//
//

#include "Logo.hpp"

void Logo::setup()
{
    fontBig.load("fonts/hirakakuW4.otf", 40);
    fontSmall.load("fonts/hirakakuW4.otf", 30);
}

void Logo::update()
{
    
}

void Logo::draw()
{
    ofPushMatrix();
    ofTranslate(330, 780);
    ofPushStyle();
    ofSetColor(ofColor::black);
	fontBig.drawString("BORDERLESS ART", -265, 99);
    fontSmall.drawString("IN", 202, 152);
	fontBig.drawString("SCARTS", 16, 219);
    ofPopStyle();
    ofPopMatrix();
}
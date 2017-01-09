//
//  Ink.cpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2017/01/06.
//
//

#include "Ink.hpp"

void Ink::setup()
{
    w = 1280;
    h = 720;
    inkSim.setup(w, h,
                 "tex/grain2.jpg",
                 "tex/alum3.jpg",
                 "tex/pinning.jpg");
    inkSim.setDrawMode(ofxInkSim::INKFIX);
    
    fbo.allocate(w, h);
    
    ofDirectory dir;
    dir.open("imgs/brush");
    dir.listDir();
    brushes.resize(dir.size());
    for (int i = 0; i < dir.size(); i++)
    {
        string path = dir.getFile(i).getAbsolutePath();
        ofLoadImage(brushes.at(i), path);
    }
    dir.close();
    
    colors.push_back(ofColor::cyan);
    colors.push_back(ofColor::magenta);
    colors.push_back(ofColor::yellow);
    c = colors.at(ofRandom(colors.size()));
    
    fadeAlpha = 255;
    circleRad = 0;
    state = DRAWABLE;
    numStroke = 0;
    lastStrokeTime = Globals::ELAPSED_TIME;
    
    inkCenter.set(ONESCRN_W/2 + 280, ONESCRN_H/2 - 60);
    
    ofAddListener(Globals::fadeout, this, &Ink::onFadeout);
}

void Ink::update()
{
    judgeDrawable();
    inkSim.update();
    
    if (state == DRAWABLE &&
        Globals::ELAPSED_TIME - lastStrokeTime > strokeInterval)
    {
        stroke();
        lastStrokeTime = Globals::ELAPSED_TIME;
    }
}

void Ink::stroke()
{
    if (state == DRAWABLE)
    {
        int brush = ofRandom(brushes.size());
        ofSetRectMode(OF_RECTMODE_CENTER);
        inkSim.begin();
        ofPushMatrix();
        ofTranslate(ofRandom(100, w-100) + 280, ofRandom(0-100, h-100) + 100, ofRandom(0, -1500));
        ofPushStyle();
        ofSetColor(getInkColor(c.getHueAngle(), ofRandom(150, 255), ofRandom(150, 220)));
        brushes.at(brush).draw(0, 0);
        ofPopStyle();
        ofPopMatrix();
        inkSim.end();
        ofSetRectMode(OF_RECTMODE_CORNER);
    }
}

void Ink::draw()
{
    fbo.begin();
    ofClear(0);
    inkSim.draw();
    fbo.end();
    
    ofPushStyle();
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    if (state == FADING)
    {
        ofSetColor(ofColor::white);
        ofDrawCircle(inkCenter, circleRad);
    }
    ofPopStyle();
}

void Ink::clear()
{
    inkSim.clear();
}

void Ink::fadeOut()
{
    state = FADING;
    Tweenzor::add(&circleRad, circleRad, 1920*0.65, 0.0f, 4.0f, EASE_OUT_CUBIC);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&circleRad), this, &Ink::onEndFadeOut);
}

void Ink::onEndFadeOut(float* arg)
{
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&circleRad));
    Tweenzor::removeTween(&circleRad);
    clear();
    fadeAlpha = 255;
    circleRad = 0;
    fadeOutTime = Globals::ELAPSED_TIME;
    state = DONEFADE;
}

void Ink::judgeDrawable()
{
    if (state == DONEFADE &&
        Globals::ELAPSED_TIME - fadeOutTime > 1.0)
    {
        state = DRAWABLE;
        c = colors.at(ofRandom(colors.size()));
        lastStrokeTime = Globals::ELAPSED_TIME;
    }
}

void Ink::onFadeout()
{
    fadeOut();
}
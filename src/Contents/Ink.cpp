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
    state = DRAWABLE;
    numStroke = 0;
    lastStrokeTime = Globals::ELAPSED_TIME;
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
        numStroke++;
        
        if (numStroke >= maxStroke)
        {
            numStroke = 0;
            fadeOut();
        }
    }
}

void Ink::stroke()
{
    if (state == DRAWABLE)
    {
        float depth = ofRandom(50, 100);
        
        int brush = ofRandom(brushes.size());
        
//        ofPoint p = getCircularRdmPos(h * 0.8, ofPoint(w/2 + 280, h/2 + 60), true);
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        inkSim.begin();
        ofPushMatrix();
        ofTranslate(ofRandom(100, w-100) + 280, ofRandom(0-100, h-100) + 100, ofRandom(0, -1500));
//        ofTranslate(p.x, p.y, ofRandom(0, -1500));
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
    ofSetColor(ofColor::white, fadeAlpha);
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
}

void Ink::clear()
{
    inkSim.clear();
}

void Ink::fadeOut()
{
    state = FADING;
    Tweenzor::add(&fadeAlpha, fadeAlpha, 0.0f, 0.0f, 3.0f, EASE_IN_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&fadeAlpha), this, &Ink::onEndFadeOut);
}

void Ink::onEndFadeOut(float* arg)
{
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&fadeAlpha));
    Tweenzor::removeTween(&fadeAlpha);
    clear();
    fadeAlpha = 255;
    fadeOutTime = Globals::ELAPSED_TIME;
    state = DONEFADE;
}

void Ink::judgeDrawable()
{
    if (state == DONEFADE &&
        Globals::ELAPSED_TIME - fadeOutTime > 5.0)
    {
        state = DRAWABLE;
        c = colors.at(ofRandom(colors.size()));
        lastStrokeTime = Globals::ELAPSED_TIME;
    }
}
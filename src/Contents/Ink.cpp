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
    int w = 1280;
    int h = 720;
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
}

void Ink::update()
{
    inkSim.update();
}

void Ink::stroke()
{
    ofColor c = ofColor::magenta;
    float depth = ofRandom(50, 100);
    
    int brush = ofRandom(brushes.size());
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    inkSim.begin();
    ofPushMatrix();
    ofTranslate(ofRandom(0, 1280), ofRandom(0, 720), ofRandom(0, -1500));
    ofPushStyle();
    ofSetColor(getInkColor(c.getHueAngle(), ofRandom(150, 255), ofRandom(150, 220)));
    brushes.at(brush).draw(0, 0);
    ofPopStyle();
    ofPopMatrix();
    inkSim.end();
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void Ink::draw()
{
    fbo.begin();
    ofClear(0);
    inkSim.draw();
    fbo.end();
    
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void Ink::clear()
{
    inkSim.clear();
}
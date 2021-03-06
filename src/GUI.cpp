//
//  GUI.cpp
//  ArtBrutCrossHotel
//
//  Created by Akira Hayasaka on 2016/12/30.
//
//

#include "GUI.hpp"

void GUI::setup(ofPtr<UniformInfos> uniforms)
{
    this->uniforms = uniforms;
    
    drawingCFSetting.setup("drawing setting");
    drawingCFSetting.add(Globals::minArea.set("Min area", 10, 1, 100));
    drawingCFSetting.add(Globals::maxArea.set("Max area", 5000, 1, 5500));
    drawingCFSetting.add(Globals::threshold.set("Threshold", 128, 0, 255));
    drawingCFSetting.add(Globals::holes.set("Holes", false));
    
    gui.setDefaultWidth(ofGetWidth() - 20);
    gui.setup(uniforms->parameters, "settings/uniforms.xml");
    gui.loadFromFile("settings/uniforms.xml");
    gui.setPosition(10, drawingCFSetting.getHeight() + 10);
    
    drawingCFSetting.setPosition(ofPoint(10, 10));
}

void GUI::update()
{

}

void GUI::draw()
{
    if (!bHide)
    {
        drawingCFSetting.draw();
        gui.draw();
    }
}

void GUI::resetToDefault()
{
    uniforms->resetToSystemDefault();
}
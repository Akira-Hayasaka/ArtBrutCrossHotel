#include "ofApp.h"

void ofApp::setup()
{
    ofEnableAlphaBlending();
    ofBackground(ofColor::white);
    ofSetVerticalSync(true);
    
    Globals::ELAPSED_TIME = ofGetElapsedTimef();
    
    Tweenzor::init();
    
    ink.setup();
    gui.setup(ink.getUniformInfo());
    gui.hide();
    ofHideCursor();
    
    lMgmt.setup(APP_W, APP_H);
    deforming = lMgmt.createLayer<Deforming>(1.0);
    
    logo.setup();
    
    numMaxRunningGlitch = 1;
    glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
    glitch.setFx(OFXPOSTGLITCH_GLOW, false);
    glitch.setFx(OFXPOSTGLITCH_SHAKER, false);
    glitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
    glitch.setFx(OFXPOSTGLITCH_TWIST, false);
    glitch.setFx(OFXPOSTGLITCH_OUTLINE, false);
    glitch.setFx(OFXPOSTGLITCH_NOISE, false);
    glitch.setFx(OFXPOSTGLITCH_SLITSCAN, false);
    glitch.setFx(OFXPOSTGLITCH_SWELL, false);
    glitch.setFx(OFXPOSTGLITCH_INVERT, false);
    glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
    glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE, false);
    glitch.setFx(OFXPOSTGLITCH_CR_REDRAISE, false);
    glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE, false);
    glitch.setFx(OFXPOSTGLITCH_CR_REDINVERT, false);
    glitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT, false);
    glitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT, false);
    glitchCandidtates.push_back(OFXPOSTGLITCH_CONVERGENCE);
    glitchCandidtates.push_back(OFXPOSTGLITCH_SHAKER);
    glitchCandidtates.push_back(OFXPOSTGLITCH_CUTSLIDER);
    glitchCandidtates.push_back(OFXPOSTGLITCH_TWIST);
    glitchCandidtates.push_back(OFXPOSTGLITCH_OUTLINE);
    glitchCandidtates.push_back(OFXPOSTGLITCH_INVERT);
    glitchCandidtates.push_back(OFXPOSTGLITCH_SLITSCAN);
    glitchCandidtates.push_back(OFXPOSTGLITCH_SWELL);
    glitch.setFbo(&lMgmt.getFramebuffer());
}

void ofApp::update()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    Globals::ELAPSED_TIME = ofGetElapsedTimef();
    
    gui.update();
    lMgmt.update();
//    updateGlitch();
    logo.update();
    ink.update();
}

void ofApp::draw()
{
    glitch.generateFx();
    
    ink.draw();
    
    ofStyle s = ofGetStyle();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    lMgmt.draw();
    logo.draw();
    glDisable(GL_BLEND);
    ofSetStyle(s);
    
    gui.draw();
    
//    ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate(), 2), 10, ofGetHeight() - 20);
}

void ofApp::keyPressed(int key)
{
    if (key == ' ')
    {
        gui.toggleVisible();
        
        if (gui.isVisible())
            ofShowCursor();
        else
            ofHideCursor();
    }
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    if (key == 'c')
    {
        ink.fadeOut();
    }
    if (key == 't')
    {
        ink.stroke();
    }
    
//    if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
//    if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW			, true);
//    if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
//    if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
//    if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, true);
//    if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
//    if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE			, true);
//    if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
//    if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL			, true);
//    if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT			, true);
//    if (key == 'q') glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
//    if (key == 'w') glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
//    if (key == 'e') glitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
//    if (key == 'r') glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
//    if (key == 't') glitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
//    if (key == 'y') glitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
//    if (key == 'u') glitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);
}

void ofApp::keyReleased(int key)
{
//    if (key == '1') glitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
//    if (key == '2') glitch.setFx(OFXPOSTGLITCH_GLOW			, false);
//    if (key == '3') glitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
//    if (key == '4') glitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
//    if (key == '5') glitch.setFx(OFXPOSTGLITCH_TWIST			, false);
//    if (key == '6') glitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
//    if (key == '7') glitch.setFx(OFXPOSTGLITCH_NOISE			, false);
//    if (key == '8') glitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
//    if (key == '9') glitch.setFx(OFXPOSTGLITCH_SWELL			, false);
//    if (key == '0') glitch.setFx(OFXPOSTGLITCH_INVERT			, false);
//    if (key == 'q') glitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
//    if (key == 'w') glitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
//    if (key == 'e') glitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
//    if (key == 'r') glitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
//    if (key == 't') glitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
//    if (key == 'y') glitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
//    if (key == 'u') glitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
}

void ofApp::updateGlitch()
{
    float rdm = ofRandomuf();
    
    if (rdm < glitchIntensity)
    {
        // push
        if (curGlitch.size() <= numMaxRunningGlitch)
        {
            bool bContain = true;
            ofxPostGlitchType tgt = glitchCandidtates.at(ofRandom(glitchCandidtates.size()));
            while (bContain)
            {
                bContain = ofContains(curGlitch, tgt);
                if (!bContain)
                {
                    curGlitch.push_back(tgt);
                    glitch.setFx(curGlitch.back(), true);
                    lastPushTime = Globals::ELAPSED_TIME;
                }
                else
                {
                    tgt = glitchCandidtates.at(ofRandom(glitchCandidtates.size()));
                }
            }
        }
    }
    
    if (Globals::ELAPSED_TIME - lastPushTime > ofRandom(0.1, 0.3))
    {
        // pop
        if (!curGlitch.empty())
        {
            glitch.setFx(curGlitch.front(), false);
            curGlitch.erase(curGlitch.begin());
        }
    }
}

void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

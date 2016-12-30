#include "ofApp.h"

void ofApp::setup()
{
    ofEnableAlphaBlending();
    ofBackground(ofColor::black);
    ofSetVerticalSync(true);
    
    Globals::ELAPSED_TIME = ofGetElapsedTimef();
    for (int i = 0; i < 10; i++)
    {
        ofFbo f;
        Globals::morphSequence.push_back(f);
        Globals::morphSequence.back().allocate(ONESCRN_W * MORPH_SEQ_RATIO,
                                               ONESCRN_H * MORPH_SEQ_RATIO);
        Globals::morphSequence.back().begin();
        ofClear(0);
        Globals::morphSequence.back().end();
    }
    
    Tweenzor::init();
    
    gui.setup();
    gui.hide();
    ofHideCursor();
    
    lMgmt.setup(APP_W, APP_H);
    deforming = lMgmt.createLayer<Deforming>(1.0);
    
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
    updateGlitch();
    glitch.generateFx();
}

void ofApp::draw()
{
    ofStyle s = ofGetStyle();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    lMgmt.draw();
    glDisable(GL_BLEND);
    ofSetStyle(s);
    
    gui.draw();
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

void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

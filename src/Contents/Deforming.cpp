//
//  Deforming.cpp
//  Entrance2
//
//  Created by Akira Hayasaka on 8/2/16.
//
//

#include "Deforming.hpp"

void Deforming::setup()
{
	int idx = 0;
    masterDir.open("imgs/deform");
    masterDir.listDir();
    for (int i = 0; i < masterDir.size(); i++)
    {
        ofFile f = masterDir.getFile(i);
        if (isImgFile(f.getExtension()))
        {
            ofPtr<Deformer> p = ofPtr<Deformer>(new Deformer);
            Deformer::ContourFinderSettings cfs;
            cfs.minArea = Globals::minArea;
            cfs.maxArea = Globals::maxArea;
            cfs.threshold = Globals::threshold;
            cfs.holes = Globals::holes;
            p->setup(f.getAbsolutePath(), cfs, idx);
            storedPuppets.push_back(p);
			idx++;
        }
    }
    
    ofRandomize(storedPuppets);
    deformTo = storedPuppets.at(getRdmIdx());
    restoreFrom = storedPuppets.at(getRdmIdx());
    
    deformTo->makeReadyToDeform(restoreFrom->getOutline());
    restoreFrom->makeReadyToRestore(deformTo->getOutline());
    
    lastDeformTime = Globals::ELAPSED_TIME;
    deformInterval = ofRandom(5.0, 10.0);
    
    deformTo->start();
    restoreFrom->start();
    bDeforming = true;
    puppetIdx = 0;
    ofAddListener(restoreFrom->finEvent, this, &Deforming::onFinishEvent);
}

void Deforming::update()
{
    int numDone = 0;
    for (auto p : storedPuppets)
    {
        if (p->isInited())
            numDone++;
    }
    
    if (numDone < storedPuppets.size())
    {
        for (auto& p : storedPuppets)
            p->update();
    }
    else
    {
        deformTo->update();
        restoreFrom->update();
        checkDeformBegin();
        
        rot.x -= 0.05;
        rot.y -= 0.05;
        rot.z -= 0.05;
    }
}

void Deforming::draw()
{
	ofPushStyle();
	//ofSetColor(ofColor::black);
    deformTo->draw(rot);
    restoreFrom->draw(rot);
	ofPopStyle();
}

int Deforming::getRdmIdx()
{
    if (puppetIdx >= masterDir.size())
        puppetIdx = 0;
    
    int rtn = puppetIdx;
    puppetIdx++;
    return rtn;
}

void Deforming::checkDeformBegin()
{
    if (!bDeforming &&
        Globals::ELAPSED_TIME - lastDeformTime > deformInterval)
    {
        lastDeformTime = Globals::ELAPSED_TIME;
        deformInterval = ofRandom(5.0, 15.0);
        
        deformTo = restoreFrom;
        restoreFrom.reset();
        restoreFrom = storedPuppets.at(getRdmIdx());
        
        deformTo->makeReadyToDeform(restoreFrom->getOutline());
        restoreFrom->makeReadyToRestore(deformTo->getOutline());
        
        deformTo->start();
        restoreFrom->start();
        
        bDeforming = true;
        ofAddListener(restoreFrom->finEvent, this, &Deforming::onFinishEvent);
        
        ofNotifyEvent(Globals::fadeout);
    }
}

void Deforming::onFinishEvent()
{
    ofRemoveListener(restoreFrom->finEvent, this, &Deforming::onFinishEvent);
    bDeforming = false;
}
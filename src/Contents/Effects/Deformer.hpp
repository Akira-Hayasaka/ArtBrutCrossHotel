//
//  Deformer.hpp
//  ShapseMorph
//
//  Created by Akira Hayasaka on 7/31/16.
//
//

#ifndef Deformer_hpp
#define Deformer_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Globals.hpp"
#include "ofxTweenzor.h"
#include "ofxCv.h"
#include "ofxTriangleMesh.h"
#include "ofxPuppetInteractive.h"

struct IdxDist
{
    int idx;
    float dist;
    ofVec2f pts;
    ofVec2f cen;
};

struct IdxAngle
{
    int idx;
    float ang;
};

struct VertexDef
{
    int idx;
    ofVec2f pts;
};

static bool compDistance(const IdxDist& p1, const IdxDist& p2)
{
    return p1.dist < p2.dist;
}

static bool compAngle(const IdxAngle& p1, const IdxAngle& p2)
{
    return p1.ang < p2.ang;
}

class Deformer : public ofThread
{
public:
    
    struct ContourFinderSettings
    {
        float minArea, maxArea, threshold;
        bool holes;
    };
    
    enum INITSTATE
    {
        NOTYET,
        UPDATED,
        DONE
    };
    INITSTATE initState;
    
    void setup(string filePath, ContourFinderSettings settings, int idx);
    void update();
    void makeReadyToDeform(ofPolyline deformTo);
    void makeReadyToRestore(ofPolyline restoreFrom);
    void start();
    void draw(ofVec3f rot);
    
    ofPolyline getOutline() { return outline; }
    bool isInited() { return (initState == DONE) ? true : false; }
    
    ofEvent<void> finEvent;
    
protected:
    
    void threadedFunction();
    
private:
    
    void setCtrlPoints();
    void getConvexHullEdges(vector<cv::Point> hullEdge);
    void getCentroid();
    void alignNumVerts();
    void makeCentroidMovePath();
    float getNearestVertex(const ofMesh& mesh, const ofVec2f& target, int& vertexIndex);    
    void onRestoreFinish(float* arg);
    
    enum TYPE
    {
        NONE,
        DEFORM,
        RESTORE
    };
    TYPE type;
    
    const int numOutlineVts = 250;
    const float morphDur = 4.0;
    const float totalDur = 15.0;

	int idx;

    string filePath;
    bool bDone;
    bool bMorphing;
    float startMorphingTime;
    float bindTexAlpha;
    ofxPuppetInteractive puppetWarp;
    ofFbo tex;
    ofFbo texForBinding;
    ofFbo screen;
    ofTexture origTex;
    ofPolyline outline;
    ofPolyline deformOutline;
    
    vector<IdxDist> edges;
    VertexDef centroid;
    vector<VertexDef> convexHullPoints;
    vector<VertexDef> morphDestinations;
    vector<VertexDef> morphProgresses;
    ofPolyline centroidMovePath;
    float centroidMovePathIdx;
    
    vector<VertexDef> labelPoints;
    
    ofVec2f seqPos;
    float lastSeqTime;
    
    int morphSeqIdx;
};

#endif /* Puppet_hpp */

#include "ofMain.h"
#include "ofApp.h"
#include "Constants.h"

int main( )
{
    ofGLFWWindowSettings settings;
	settings.setSize(APP_W, APP_H);
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}

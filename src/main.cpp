#include "ofMain.h"
#include "ofApp.h"
#include "Constants.h"

int main( )
{
    ofGLFWWindowSettings settings;
    settings.width = APP_W;
    settings.height = APP_H;
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}

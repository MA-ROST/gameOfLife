#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	const string title               = "Game Of Life";
	constexpr Point <int> screenSize = {600, 600};

	ofGLFWWindowSettings settings;
	settings.setSize(screenSize.x, screenSize.y);
	settings.title = title;
	settings.resizable = false;
	ofCreateWindow(settings);
	ofSetFrameRate(24);
	ofSetWindowTitle(title); // Set the window title


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}

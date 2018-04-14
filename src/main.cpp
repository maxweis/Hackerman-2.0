#include "ofMain.h"
#include "ofApp.h"

int main( ){
  //setup OpenGL context
	ofSetupOpenGL(1920, 1080, OF_WINDOW);

	ofRunApp(new Hackerman());
}

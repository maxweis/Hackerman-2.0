#include "render.h"
#include "ofApp.h"

void Hackerman::ClearScreen() {
  ofSetColor(kBlack);
  ofFill();
  ofDrawRectangle(0, 0, screen.width, screen.height);
}

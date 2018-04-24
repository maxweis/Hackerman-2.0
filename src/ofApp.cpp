#include "ofApp.h"

//--------------------------------------------------------------
void Hackerman::setup(){
  ofSetFrameRate(60.0);

  ofSetWindowShape(screen.width, screen.height);

  ofSetWindowTitle("Hackerman");

  font_inconsolata14.load("font/inconsolata.ttf", 14);

  startMusicLoop();

  InitPanels();
}

//--------------------------------------------------------------
void Hackerman::update(){
}

//--------------------------------------------------------------
void Hackerman::draw(){
  DrawPanels();
}

//--------------------------------------------------------------
void Hackerman::keyPressed(int key){
  if (console_panel.has_focus) {
    console_panel.current_command << (char) key;
  }
}

//--------------------------------------------------------------
void Hackerman::keyReleased(int key){

}

//--------------------------------------------------------------
void Hackerman::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Hackerman::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Hackerman::mousePressed(int x, int y, int button){
  ofRectangle click_rectangle = ofRectangle(x, y, 1, 1);

  for (auto &enemy_panel : enemy_panels) {
    if (click_rectangle.intersects((ofRectangle) enemy_panel)) {
      enemy_panel.Focus();
    }
  }

  for (auto &util_button : util_buttons) {
    if (click_rectangle.intersects((ofRectangle) util_button)) {
      HandleUtilButtonAction((UtilButtonType) util_button.number);
    }
  }

  if (click_rectangle.intersects((ofRectangle) console_panel)) {
    console_panel.Focus();
  }
}

//--------------------------------------------------------------
void Hackerman::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Hackerman::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void Hackerman::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void Hackerman::windowResized(int w, int h){
}

//--------------------------------------------------------------
void Hackerman::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Hackerman::dragEvent(ofDragInfo dragInfo){ 

}

void Hackerman::SetResolution(int width, int height) {
  screen.width = width;
  screen.height = height;
}

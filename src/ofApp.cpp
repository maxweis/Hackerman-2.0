#include "ofApp.h"

//--------------------------------------------------------------
void Hackerman::setup(){
  screen = ofRectangle(0, 0, 1920, 1080); 

  ofSetWindowTitle("Hackerman");

  font_inconsolata14.load("font/inconsolata.ttf", 14);

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

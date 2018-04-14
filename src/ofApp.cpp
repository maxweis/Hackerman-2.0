#include "ofApp.h"

//--------------------------------------------------------------
void Hackerman::setup(){
  ofSetWindowTitle("Hackerman");

  screen_width = 1920;
  screen_height = 1080;

  font_inconsolata14.load("/home/max/git/final-project-maxweis/assets/font/inconsolata.ttf", 14);

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

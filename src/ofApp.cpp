#include "ofApp.h"
#include <boost/algorithm/string.hpp>
#include "filesystem.h"
#include "store.h"

void Hackerman::setup(){
  ofSetFrameRate(kFPS);

  ofSetWindowShape(screen.width, screen.height);

  ofSetWindowTitle("Hackerman");

  font_inconsolata14.load("font/inconsolata.ttf", 14);

  startMusicLoop();

  InitPanels();


  //initialize filesystem images to be loaded later
  InitFileImages();
  InitFilesystem();
  main_panel.state = FILESYSTEM;

  InitStoreImages();
  InitUpgrades();

  PrintToConsole("Welcome to the Hackerman 1.9.8 Mainframe");
  PrintToConsole("Type \"help\" for usage instructions");
  PrintToConsole("");
}

void Hackerman::update(){
  if (player.connected && EnemiesAlive() != 0) {
    UpdateEnemies();
  }
  UpdatePlayer();
}

void Hackerman::draw(){
  DrawPanels();
}

void Hackerman::keyPressed(int key){
  //console input controls
  if (console_panel.has_focus) {
    if (key == OF_KEY_RETURN) {
      if (console_panel.user_prompted) {
        HandleUtilButtonAction(console_panel.state);
      } else {
        ProcessCommand();
      }
    }

    if (key == OF_KEY_BACKSPACE) {
      //clear last character of current command stringstream
      std::string command = console_panel.current_command.str();
      command = command.substr(0, command.length() - 1);
      console_panel.current_command.str("");
      console_panel.current_command << command;
    }

    //check if key should be displayed in terminal (a-z or space)
    if (key >= 'a' && 'z' >= key) {
      if (ofGetKeyPressed(kShiftKey)) {
        console_panel.current_command << (char) toupper(key);
      } else {
        console_panel.current_command << (char) key;
      }
    } else if (('!' <= key && '_' >= key) || key == ' ') {
      console_panel.current_command << (char) key;
    }
  }
}

void Hackerman::keyReleased(int key){

}

void Hackerman::mouseMoved(int x, int y ){

}

void Hackerman::mouseDragged(int x, int y, int button){

}

void Hackerman::mousePressed(int x, int y, int button){
  ofRectangle click_rectangle = ofRectangle(x, y, 1, 1);

  if (player.connected) {
    for (auto &enemy_panel : enemy_panels) {
      if (click_rectangle.intersects((ofRectangle) enemy_panel)) {
        enemy_panel.Focus();
      }
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

  if (main_panel.state == FILESYSTEM) {
    //check directories to see if clicked
    for (unsigned int i = 0; i < current_dir.files.size(); i++) {
      if (click_rectangle.intersects(current_dir.files[i].bound)) {
        if (current_dir.files[i].file_type == FOLDER) {
            current_dir = File(current_dir.files[i]);
        }
        if (current_dir.files[i].file_type == EXECUTABLE) {}
            HandleUtilButtonAction(current_dir.files[i].program);
      }
    }
  } else if (main_panel.state == STORE) { 
    //check upgrades to see if clicked
    for (unsigned int i = 0; i < upgrades.size(); i++) {
      if (click_rectangle.intersects(upgrades[i].bound)) {
        BuyUpgrade(upgrades[i].type);
      }
    }
  }
}

void Hackerman::mouseReleased(int x, int y, int button){

}

void Hackerman::mouseEntered(int x, int y){

}

void Hackerman::mouseExited(int x, int y){

}

void Hackerman::windowResized(int w, int h){
  if (w != screen.width || h != screen.height) {
    ofSetWindowShape(screen.width, screen.height);
  }
}

void Hackerman::gotMessage(ofMessage msg){

}

void Hackerman::dragEvent(ofDragInfo dragInfo){ 

}

void Hackerman::SetResolution(int width, int height) {
  screen.width = width;
  screen.height = height;
}

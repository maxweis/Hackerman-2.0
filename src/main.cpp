#include "ofMain.h"
#include "ofApp.h"

int main(int argc, char *argv[]){
  int screen_width = 1920;
  int screen_height = 1080;

  if (argc >= 3) {
    screen_width = std::stoi(argv[1]);
    screen_height = std::stoi(argv[2]);
  }

  ofSetupOpenGL(screen_width, screen_height, OF_WINDOW);

  auto game = new Hackerman();

  game->SetResolution(screen_width, screen_height);

	ofRunApp(game);
}

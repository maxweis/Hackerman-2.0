#include "sound.h"
#include "ofApp.h"

//start music loop played throughout game
void Hackerman::startMusicLoop() {
  music_loop.load("music/streetlight_8-bit_medley.mp3");
  music_loop.setLoop(true);
  music_loop.play();
}

#include "player.h"
#include "ofApp.h"
#include <algorithm>
#include "enemy.h"

//borrowed from stack overflow
//https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
std::string GetRandomPassword(int length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };

    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

//check and update the state of the player
void Hackerman::UpdatePlayer() {
  if (!player.password_encrypted && !player.firewall_up) {
    player.defeated = true;
    PrintToConsole("You have failed. The enemies defeated you.");
    std::cout << "You have failed. The enemies defeated you." << std::endl;
    ofExit(0);
  }

  //check if player has won
  if (EnemiesAlive() == 0) {
    PrintToConsole("You have succeeded. You have defeated all of the enemies.");
    std::cout << "You have succeeded. You have defeated all of the enemies." << std::endl;
    ofExit(0);
  }
}

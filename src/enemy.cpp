#include <sstream>
#include "enemy.h"
#include "ofMain.h"

//generate unique random name from name list
std::string GetRandomEnemyName() {
  static bool name_used[kEnemyNamesAmount] = { false };

  if (kEnemyAmount > kEnemyNamesAmount) {
    std::cerr << "Not enough enemy names for enemy amount" << std::endl;
    exit(1);
  }

  int random_index;
  //attempt to access unique enemy name
  do {
    random_index = (int) ofRandom(0, kEnemyNamesAmount);
  } while (name_used[random_index]);

  //set name as used
  name_used[random_index] = true;

  return kEnemyNames[random_index];
}

std::string GetRandomIpString() {
  std::ostringstream ip_address;

  int ip_subsections = 4;
  //add random numbers in 0-255 range to stringstring to mock ip address
  for (int i = 0; i < ip_subsections - 1; i++) {
    ip_address << std::to_string((int) ofRandom(0, 255)) << ".";
  }
  ip_address << std::to_string((int) ofRandom(0, 255));

  return ip_address.str();
}

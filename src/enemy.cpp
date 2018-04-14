#include <sstream>
#include "enemy.h"
#include "ofMain.h"

std::string GetRandomEnemyName() {
  static bool name_used[kEnemyNamesAmount] = { false };

  int random_index;
  do {
    random_index = (int) ofRandom(0, kEnemyNamesAmount);
  } while (name_used[random_index]);

  name_used[random_index] = true;

  return kEnemyNames[random_index];
}

std::string GetRandomIpString() {
  std::ostringstream ip_address;

  int ip_subsections = 4;
  for (int i = 0; i < ip_subsections - 1; i++) {
    ip_address << std::to_string((int) ofRandom(0, 255)) << ".";
  }
  ip_address << std::to_string((int) ofRandom(0, 255));

  return ip_address.str();
}

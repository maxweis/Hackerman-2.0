#include <sstream>
#include "enemy.h"
#include "ofMain.h"
#include "ofApp.h"

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

void Hackerman::UpdateEnemies() {
}

Enemy *Hackerman::GetFocusedEnemy() {
  for (EnemyPanel &enemy_panel : enemy_panels) {
    if (enemy_panel.has_focus) {
      return &enemy_panel.enemy;
    }
  }

  //no enemy focused
  return nullptr;
}

int Hackerman::EnemiesAlive() {
  int enemies_alive = 0;
  for (EnemyPanel enemy_panel : enemy_panels) {
    if (!enemy_panel.enemy.defeated) {
      enemies_alive++;
    }
  }

  return enemies_alive;
}

bool Hackerman::PasswordGuess(std::string guess, std::string password) {
  if (guess.length() != password.length()) {
    PrintToConsole("Password length is " + std::to_string(password.length()));
    return false;
  }

  if (guess == password) {
    return true;
  }

  std::string guess_string;
  for (unsigned int i = 0; i < password.length(); i++) {
    if (password[i] == guess[i]) {
      guess_string += password[i];
    } else {
      guess_string += "_";
    }
  }
  PrintToConsole("Characters of password guessed: " + guess_string);

  return false;
}

void Hackerman::RestoreEnemyFirewalls() {
  for (EnemyPanel &enemy_panel : enemy_panels) {
    enemy_panel.enemy.firewall_up = true;
  }
}

void Hackerman::DefeatEnemy(Enemy &enemy) {
  enemy.defeated = true;
  PrintToConsole(enemy.name + "'s Bitcoin wallet has been decrypted. \
You have gained " + std::to_string(enemy.bitcoin) + " BTC.");
  player.bitcoin += enemy.bitcoin;
}

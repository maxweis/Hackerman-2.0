#include <sstream>
#include "enemy.h"
#include "ofMain.h"
#include "ofApp.h"

//return the name of a random enemy which has not been defeated
std::string Hackerman::GetRandomLivingEnemyName() {
  std::string name;
  int random_enemy_number;

  do {
    random_enemy_number = ofRandom(0, enemy_panels.size());
    name = enemy_panels[random_enemy_number].enemy.name;
  } while (enemy_panels[random_enemy_number].enemy.defeated);

  return enemy_panels[random_enemy_number].enemy.name;
}

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

//return a fake ip string for enemies
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
  //check if time has expired on enemy firewall going down
  for (EnemyPanel &enemy_panel : enemy_panels) {
    if (enemy_panel.enemy.firewall_attacked) {
      float time = ofGetElapsedTimef() - enemy_panel.enemy.firewall_strength;
      if (enemy_panel.enemy.firewall_attack_time <= time) {
        enemy_panel.enemy.firewall_up = false;
        enemy_panel.enemy.firewall_attacked = false;
      }
    }
  }

  //enemies randomly attack player, based on player upgrades
  int probability = ofRandom(0, 1800 * player.defense);
  if (probability == 1) {
    if (player.firewall_up) {
      player.firewall_up = false;
      PrintToConsole("Your firewall has been take offline by " +
          GetRandomLivingEnemyName() + ".");
    } else {
      player.password_encrypted = false;
      PrintToConsole("Your bitcoin wallet has been decrypted and stolen by " +
          GetRandomLivingEnemyName() + ".");
    }
  }
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

//user interface for bruteforcing password when decrypting
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

//called when enemy defeated
void Hackerman::DefeatEnemy(Enemy &enemy) {
  enemy.defeated = true;
  PrintToConsole(enemy.name + "'s Bitcoin wallet has been decrypted. \
You have gained " + std::to_string(enemy.bitcoin) + " BTC.");
  player.bitcoin += enemy.bitcoin;
}

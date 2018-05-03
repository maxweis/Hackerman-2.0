#include "panel.h"
#include "ofApp.h"
#include "enemy.h"
#include <array>
#include <string>
#include <memory>
#include <pstream.h>
#include <cstdio>
#include <sstream>
#include <boost/algorithm/string.hpp>

void Hackerman::InitEnemyPanel() {
  //enemy panel dimensions
  float enemy_panel_width = screen.width * kEnemyPanelWidthRatio;
  float enemy_panel_height = screen.height / kEnemyAmount;

  //create kEnemyAmount panels of same height and width
  for (int i = 0; i < kEnemyAmount; i++) {
    ofRectangle enemy_panel_rect = ofRectangle(0, enemy_panel_height * i, enemy_panel_width, enemy_panel_height);
    enemy_panels.push_back(EnemyPanel(enemy_panel_rect, i + 1));
  }
}

void Hackerman::InitConsolePanel() {
  //create rectangle for console panel
  float console_panel_width = screen.width - enemy_panels[0].width;
  float console_panel_height = screen.height * kConsolePanelHeightRatio;
  ofRectangle console_panel_rect = ofRectangle(enemy_panels[0].width, (1 - kConsolePanelHeightRatio) * screen.height, console_panel_width, console_panel_height);
  console_panel = ConsolePanel(console_panel_rect);
}

void Hackerman::InitUtilPanel() {
  //individual button dimensions
  float util_button_width = (screen.width * kUtilButtonWidthRatio) / kUtilButtonColumns;
  float util_button_height = (screen.height - console_panel.height) / kUtilButtonRows;

  for (int row = 0; row < kUtilButtonRows; row++) {
    for (int column = 0; column < kUtilButtonColumns; column++) {
      //specific button coordinates
      float util_button_x = screen.width - (screen.width * kUtilButtonWidthRatio) + util_button_width * column;
      float util_button_y = row * util_button_height;
      int button_number = row * kUtilButtonColumns + column;
      ofRectangle util_button_rect = ofRectangle(util_button_x, util_button_y, util_button_width, util_button_height);
      std::string button_icon_path = kUtilButtonIconPaths[button_number];

      //add image if present
      ofImage *image = nullptr;
      if (!button_icon_path.empty()) {
        image = new ofImage(button_icon_path);
      }

      util_buttons.push_back(UtilButton(util_button_rect, button_number, row, column, image));
    }
  }
}

void Hackerman::InitMainPanel() {
  //main panel dimensions
  float main_panel_width = screen.width - enemy_panels[0].width - (util_buttons[0].width * kUtilButtonColumns);
  float main_panel_height = screen.height - console_panel.height;

  ofRectangle main_panel_rect = ofRectangle(enemy_panels[0].width, 0, main_panel_width, main_panel_height);

  main_panel = Panel(main_panel_rect);
}

void Hackerman::InitPanels() {
  InitEnemyPanel();
  InitConsolePanel();
  InitUtilPanel();
  InitMainPanel();
}

void EnemyPanel::Focus() {
  auto game_state = (Hackerman*) ofGetAppPtr();

  //toggle focus
  if (!has_focus) {
    for (auto &enemy_panel : game_state->enemy_panels) {
      enemy_panel.has_focus = false;
    }

    has_focus = true;
  } else {
    has_focus = false;
  }
}

//handle buttons pressed on panel on right side of screen
void Hackerman::HandleUtilButtonAction(UtilButtonType button_type) {
  switch (button_type) {
    case CONNECT:
      if (!player.connected) {
        ofSleepMillis(500);
        PrintToConsole("Connected to enemies.");
        player.connected = true;
      }
      break;
    case DISCONNECT:
      if (player.connected) {
        ofSleepMillis(500);
        PrintToConsole("Disconnected from enemies. Enemy firewalls restored.");
        RestoreEnemyFirewalls();
        player.connected = false;
      }
      break;
    case FIREWALL_UP:
      if (player.firewall_up) {
        PrintToConsole("Firewall already deployed.");
      } else {
        ofSleepMillis(500);
        PrintToConsole("Firewall deployed.");
        player.firewall_up = true;
      }
      break;
    case ENCRYPT:
      OpenEncryptInterface();
      break;
    case FILESYSTEM:
      OpenFilesystemInterface();
      break;
    case STORE:
      OpenStoreInterface();
      break;
    case FIREWALL_ATTACK:
      if (player.connected) {
        OpenFirewallAttackInterface();
      } else {
        PrintToConsole("Not connected to enemies.");
      }
        break;
    case DECRYPT:
      if (player.connected) {
        OpenDecryptInterface();
      } else {
        PrintToConsole("Not connected to enemies.");
      }
      break;
  }
}

void Hackerman::PrintToConsole(std::string message, bool console_prefix) {
  std::string prefix_text = "";
  if (console_prefix) {
    prefix_text = "HM 1.9.8: ";
  }

  console_panel.history.push_front(prefix_text + message);
}

void Hackerman::PrintToConsole(std::vector<std::string> messages) {
  for (std::string message : messages) {
    console_panel.history.push_front(message);
  }
}

void Hackerman::ProcessCommand() {
  std::string command = console_panel.current_command.str();

  //convert string to lowercase if not in sh mode
  if (!console_panel.sh_enabled) {
    boost::to_lower(command);
  }
  boost::trim(command);

  //clear current command
  std::stringstream().swap(console_panel.current_command);

  if (command  == "exit" || command == "quit") {
    if (console_panel.sh_enabled) {
      PrintToConsole("sh mode exited");
      PrintToConsole("");
      console_panel.sh_enabled = false;
    } else {
      ofExit();
    }
  }
  //handle sh commands if in sh mode
  else if (console_panel.sh_enabled) {
    PrintToConsole(console_panel.sh_exec(command));
  } else if (command == "clear") {
    console_panel.history.clear();
  } else if (command == "help") {
    PrintToConsole("wat a n00b");
    PrintToConsole("for real view README.md for instructions");
  } else if (command == "") {
    PrintToConsole("");
  } else if (command == "sh" && player.sh_unlocked) {
    PrintToConsole("sh mode entered");
    PrintToConsole("");
    console_panel.sh_enabled = true;
  } else if (command == "maxiscool") {
    //cheat code 
    player.sh_unlocked = true;
    player.defense++;
  } else if (command == "connect") {
    HandleUtilButtonAction(CONNECT);
  } else if (command == "disconnect") {
    HandleUtilButtonAction(DISCONNECT);
  } else if (command == "firewall up") {
    HandleUtilButtonAction(FIREWALL_UP);
  } else if (command == "encrypt") {
    HandleUtilButtonAction(ENCRYPT);
  } else if (command == "filesystem") {
    HandleUtilButtonAction(FILESYSTEM);
  } else if (command == "store") {
    HandleUtilButtonAction(STORE);
  } else if (command == "firewall attack") {
    HandleUtilButtonAction(FIREWALL_ATTACK);
  } else if (command == "decrypt") {
    HandleUtilButtonAction(DECRYPT);
  } else {
    PrintToConsole("\"" + command + "\""  " not recognized", true);
  }
}

//inspired by https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
std::vector<std::string> ConsolePanel::sh_exec(std::string cmd) { 
  redi::ipstream proc(cmd.c_str(), redi::pstreams::pstdout | redi::pstreams::pstderr);
  std::string line;
  std::vector<std::string> command_output;

  while (std::getline(proc.out(), line)) {
    command_output.push_back(line);
  }

  while (std::getline(proc.err(), line)) {
    command_output.push_back(line);
  }

  command_output.push_back("\n");
  return command_output;
}

void Hackerman::OpenEncryptInterface() {
  if (current_dir.name != "/etc") {
    PrintToConsole("File not found to encrypt.");
  } else {
    if (!console_panel.user_prompted) {
      PrintToConsole("Enter encryption password:");
      console_panel.user_prompted = true;
      console_panel.state = ENCRYPT;
    } else {
      //register user input
      player.password = console_panel.current_command.str();
      boost::trim(player.password);
      //clear current input to console
      console_panel.current_command.str("");

      console_panel.user_prompted = false;
      player.password_encrypted = true;
      PrintToConsole("Password file successfully encrypted.");
    }
  }
}

//attacking enemy firewall interface
void Hackerman::OpenFirewallAttackInterface() {
  Enemy *enemy = GetFocusedEnemy();

  if (!enemy) {
    PrintToConsole("No enemy selected.");
    return;
  }

  if (!enemy->firewall_up) {
    PrintToConsole("The enemy's firewall is down.");
    return;
  }

  if (enemy->firewall_attacked) {
      int time_left = enemy->firewall_attack_time + enemy->firewall_strength - ofGetElapsedTimef();
      PrintToConsole("The enemy's firewall will be down in " + 
          std::to_string(time_left + 1) + " seconds.");
      return;
  }

  PrintToConsole("Firewall being attacked. Enemy firewall offline in " +
      std::to_string(enemy->firewall_strength) + " seconds.");
  enemy->firewall_attack_time = ofGetElapsedTimef();
  enemy->firewall_attacked = true;
}

void Hackerman::OpenDecryptInterface() {
  if (!GetFocusedEnemy()) {
    PrintToConsole("No enemy selected.");
    return;
  }

  Enemy *enemy = GetFocusedEnemy();

  if (enemy->firewall_up) {
    PrintToConsole("The enemy's firewall is up. You can not decrypt their bitcoin wallet.");
    return;
  }

  if (!console_panel.user_prompted) {
    PrintToConsole("Enter decryption password:");
    console_panel.user_prompted = true;
    console_panel.state = DECRYPT;
  } else {
    std::string password = console_panel.current_command.str();
    boost::trim(password);

    //clear current input to console
    console_panel.current_command.str("");

    if (PasswordGuess(password, enemy->password)) {
      DefeatEnemy(*enemy);
    }

    console_panel.user_prompted = false;
  }
}

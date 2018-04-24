#include "panel.h"
#include "ofApp.h"
#include "enemy.h"

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

void Panel::Focus() {
  auto game_state = (Hackerman*) ofGetAppPtr();

  for (auto &enemy_panel : game_state->enemy_panels) {
    enemy_panel.has_focus = false;
  }

  game_state->console_panel.has_focus = false;

  has_focus = true;
}

void Hackerman::HandleUtilButtonAction(UtilButtonType button_type) {
  switch (button_type) {
    case CONNECT:
      console_panel.history.push_front("Connected to enemies");
      player.connected = true;
      break;
    case DISCONNECT:
      console_panel.history.push_front("Disconnected from enemies");
      player.connected = false;
      break;
    case FIREWALL_UP:
      console_panel.history.push_front("Firewall online");
      player.defense = 1;
      break;
    case ENCRYPT:
      std::cout <<"encrypt"<< std::endl;
      break;
    case FILESYSTEM:
      std::cout <<"filesystem"<< std::endl;
      break;
    case STORE:
      std::cout <<"store"<< std::endl;
      break;
    case FIREWALL_ATTACK:
      std::cout <<"firewall attack"<< std::endl;
      break;
    case DECRYPT:
      std::cout <<"decrypt"<< std::endl;
      break;
  }
}

void Hackerman::PrintToConsole(std::string message) {
  console_panel.history.push_front(message);
}

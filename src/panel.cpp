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
      ofRectangle util_button_rect = ofRectangle(util_button_x, util_button_y, util_button_width, util_button_height);
      std::string button_icon_path = kUtilButtonIconPaths[row * kUtilButtonColumns + column];

      //add image if present
      ofImage *image = nullptr;
      if (!button_icon_path.empty()) {
        image = new ofImage(button_icon_path);
      }

      util_buttons.push_back(UtilButton(util_button_rect, row, column, image));
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

void Hackerman::DrawEnemyPanel() {
  ofNoFill();
  ofSetColor(kMainColor);
  ofSetLineWidth(kLineWidth);

  //ratio of height for y coordinate of enemy panel
  float name_align_ratio = 3.0 / 4.0;
  float ip_align_ratio = 1.0 / 3.0;
  for (EnemyPanel enemy_panel : enemy_panels) {
    ofDrawRectangle((ofRectangle) enemy_panel);
    //draw panel number
    font_inconsolata14.DrawTopLeftAlign(std::to_string(enemy_panel.enemy_number), (ofRectangle) enemy_panel, kMainColor, kBorderWidth);
    //draw enemy name
    font_inconsolata14.DrawCenterAlignX(enemy_panel.name, (ofRectangle) enemy_panel, name_align_ratio, kMainColor);
    //draw enemy ip
    font_inconsolata14.DrawCenterAlignX(enemy_panel.ip, (ofRectangle) enemy_panel, ip_align_ratio, kMainColor);
  }
}

void Hackerman::DrawConsolePanel() {
  ofNoFill();
  ofSetColor(kMainColor);
  ofSetLineWidth(kLineWidth);

  //draw frame
  ofDrawRectangle((ofRectangle) console_panel);
  //draw prompt
  font_inconsolata14.DrawBottomLeftAlign(">>", console_panel.x + kBorderWidth, console_panel.y + console_panel.height - kBorderWidth, kMainColor);
}

void Hackerman::DrawUtilPanel() {
  ofNoFill();
  ofSetColor(kWhite);
  ofSetLineWidth(kLineWidth);

  for (UtilButton util_button : util_buttons) {
    //draw borders
      ofDrawRectangle((ofRectangle) util_button);
      if (util_button.icon) {
        //draw icon
        util_button.icon->draw((ofRectangle) util_button);
      }
  }
}

void Hackerman::DrawMainPanel() {
  ofNoFill();
  ofSetColor(kWhite);
  ofSetLineWidth(kLineWidth);

  //draw border
  ofDrawRectangle((ofRectangle) main_panel);

  //draw centered example text
  font_inconsolata14.DrawCenterAlign("Main area", (ofRectangle) main_panel, kMainColor);
}

void Hackerman::DrawPanels() {
  ClearScreen();
  DrawEnemyPanel();
  DrawConsolePanel();
  DrawUtilPanel();
  DrawMainPanel();
}

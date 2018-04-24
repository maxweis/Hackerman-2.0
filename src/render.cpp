#include "render.h"
#include "ofApp.h"

void Hackerman::ClearScreen() {
  ofSetColor(kBlack);
  ofFill();
  ofDrawRectangle(0, 0, screen.width, screen.height);
}

void Hackerman::DrawConsolePanel() {
  ofNoFill();
  ofSetColor(kMainColor);
  ofSetLineWidth(kLineWidth);

  //draw frame
  ofDrawRectangle((ofRectangle) console_panel);
  //draw prompt
  font_inconsolata14.DrawBottomLeftAlign(">>" + console_panel.current_command.str(), console_panel.x + kBorderWidth, console_panel.y + console_panel.height - kBorderWidth, kMainColor);

  //get max text size
  ofRectangle font_size = font_inconsolata14.getStringBoundingBox("|", 0, 0);

  int console_columns = (console_panel.height - font_size.height) / (font_size.height);

  for (int i = 0; i < console_panel.history.size() && i < console_columns; i++) {
    font_inconsolata14.DrawBottomLeftAlign(console_panel.history[i], console_panel.x + kBorderWidth,
        console_panel.y + console_panel.height - (kBorderWidth * 2) - (i + 1) * font_size.height, kMainColor);
  }
}

void Hackerman::DrawUtilPanel() {
  ofNoFill();
  ofSetLineWidth(kLineWidth);
  ofSetColor(kWhite);

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
  // font_inconsolata14.DrawCenterAlign("Main area", (ofRectangle) main_panel, kMainColor);
}

void Hackerman::DrawPanels() {
  ClearScreen();

  if (player.connected) {
    DrawEnemyPanel();
  }

  DrawConsolePanel();
  DrawUtilPanel();
  DrawMainPanel();
}

void Hackerman::DrawEnemyPanel() {
  ofNoFill();
  ofSetColor(kMainColor);
  ofSetLineWidth(kLineWidth);

  //ratio of height for y coordinate of enemy panel
  float name_align_ratio = 3.0 / 4.0;
  float ip_align_ratio = 1.0 / 3.0;
  for (EnemyPanel enemy_panel : enemy_panels) {
    ofColor panel_color = kMainColor;
    ofSetColor(kMainColor);

    ofDrawRectangle((ofRectangle) enemy_panel);

    //change text rendering color to white if focused
    if (enemy_panel.has_focus) {
      panel_color = kWhite;
    }

    //draw panel number, get box drawn in
    font_inconsolata14.DrawTopLeftAlign(std::to_string(enemy_panel.enemy_number), (ofRectangle) enemy_panel, panel_color, kBorderWidth);
    //draw enemy name
    font_inconsolata14.DrawCenterAlignX(enemy_panel.name, (ofRectangle) enemy_panel, name_align_ratio, panel_color);
    //draw enemy ip
    font_inconsolata14.DrawCenterAlignX(enemy_panel.ip, (ofRectangle) enemy_panel, ip_align_ratio, panel_color);
  }
}


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
  //draw prompt show as white if focused
  if (console_panel.has_focus) {
    font_inconsolata14.DrawBottomLeftAlign(">> " + console_panel.current_command.str(),
        console_panel.x + kBorderWidth, console_panel.y + console_panel.height - kBorderWidth, kWhite);
  } else {
    font_inconsolata14.DrawBottomLeftAlign(">> " + console_panel.current_command.str(), 
        console_panel.x + kBorderWidth, console_panel.y + console_panel.height - kBorderWidth, kMainColor);
  }

  //get max text size
  ofRectangle font_size = font_inconsolata14.getStringBoundingBox("|", 0, 0);

  unsigned int console_columns = (console_panel.height - font_size.height) / (font_size.height);

  for (unsigned int i = 0; i < console_panel.history.size() && i < console_columns; i++) {
    font_inconsolata14.DrawBottomLeftAlign(console_panel.history[i], console_panel.x + kBorderWidth,
        console_panel.y + console_panel.height - kBorderWidth - (i + 1) * font_size.height, kMainColor);
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
  if (main_panel.state == FILESYSTEM) {
    DrawFilesystemInterface();
  } else if (main_panel.state == STORE) {
    DrawStoreInterface();
  }
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
    //do not draw panel if defeated
    if (enemy_panel.enemy.defeated) {
      continue;
    }

    ofColor panel_color = kMainColor;
    ofSetColor(kMainColor);

    ofDrawRectangle((ofRectangle) enemy_panel);

    //change text rendering color to white if focused
    if (enemy_panel.has_focus) {
      panel_color = kWhite;
    }

    //draw panel number, get box drawn in
    font_inconsolata14.DrawTopLeftAlign(std::to_string(enemy_panel.enemy.number), (ofRectangle) enemy_panel, panel_color, kBorderWidth);
    //draw enemy name
    font_inconsolata14.DrawCenterAlignX(enemy_panel.enemy.name, (ofRectangle) enemy_panel, name_align_ratio, panel_color);
    //draw enemy ip
    font_inconsolata14.DrawCenterAlignX(enemy_panel.enemy.ip, (ofRectangle) enemy_panel, ip_align_ratio, panel_color);
  }
}

//center align image on screen
ofRectangle Hackerman::DrawCenterAlign(ofImage &image, ofRectangle bound) {
  ofSetColor(kWhite);

  float bound_center_x = bound.x + (bound.width / 2) - (image.getWidth() / 2);
  float bound_center_y = bound.y + (bound.height / 2) - (image.getHeight() / 2);

  ofRectangle image_box = ofRectangle(bound_center_x, bound_center_y,
      image.getWidth(), image.getHeight());

  image.draw(image_box);

  return image_box;
}

//align image to center with a ratio for the y coordinate on the bound
ofRectangle Hackerman::DrawCenterAlignX(ofImage &image, ofRectangle bound, float y_ratio) {
  ofSetColor(kWhite);

  float bound_center_x = bound.x + (bound.width / 2) - (image.getWidth() / 2);
  float bound_y = bound.y + (bound.height * y_ratio) - (image.getHeight() / 2);

  ofRectangle image_box = ofRectangle(bound_center_x, bound_y,
    image.getWidth(), image.getHeight());

  image.draw(image_box);

  return image_box;
}

#pragma once

#include "ofMain.h"
#include "enemy.h"
#include <vector>

enum UtilButtonType {
  CONNECT,
  DISCONNECT,
  FIREWALL_UP,
  ENCRYPT,
  FILESYSTEM,
  STORE,
  FIREWALL_ATTACK,
  DECRYPT
};

class Panel : public ofRectangle {
  public:
    Panel() : has_focus(false) {}
    Panel(ofRectangle bound) : ofRectangle(bound), has_focus(false),
    background_color(ofColor(0, 0, 0, 255)) {}

    void Focus();

    bool has_focus;
    ofColor background_color;
};

class EnemyPanel : public Panel {
  public:
    EnemyPanel() {}
    EnemyPanel(ofRectangle bound, int enemy_number)
      : Panel(bound), enemy_number(enemy_number), name(GetRandomEnemyName()), 
      ip(GetRandomIpString()) {}

    std::string name;
    int enemy_number;
    std::string ip;
};

class UtilButton : public Panel {
  public:
    UtilButton() {}
    UtilButton(ofRectangle bound, int button_number, int row, int column,
        ofImage *icon) 
      : Panel(bound), number(button_number), row(row), column(column), 
      icon(icon) {}
    // ~UtilButton();

    std::string title;
    ofImage *icon;

    //number int 0-indexed
    int number, row, column;
};

class ConsolePanel : public Panel {
  public:
    ConsolePanel() {}
    ConsolePanel(ofRectangle bound) : Panel(bound) {}

    std::deque<std::string> history;
    std::stringstream current_command;
};

//percentage of screen enemy panel takes up horizontally
float const kEnemyPanelWidthRatio = 1.0 / 5.0;

//percentage of screen console takes up vertically
float const kConsolePanelHeightRatio = 3.0 / 10.0;

int const kUtilButtonRows = 4;
int const kUtilButtonColumns = 2;
int const kUtilButtonAmount = kUtilButtonRows * kUtilButtonRows;
float const kUtilButtonWidthRatio = 1.0 / 5.0;
const std::vector<std::string> kUtilButtonIconPaths = {"icons/connect.png", "icons/disconnect.png", "icons/firewall_up.png", "icons/encrypt.png",
"icons/files.png", "icons/bitcoin.png", "icons/firewall_attack.png", "icons/decrypt.png"};

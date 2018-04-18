#pragma once

#include "ofMain.h"
#include "enemy.h"
#include <vector>

class Panel : public ofRectangle {
  public:
    Panel() : has_focus(false) {}
    Panel(ofRectangle bound) : ofRectangle(bound), has_focus(false) {}
    Panel(float x, float y, float width, float height) : ofRectangle(x, y, width, height), has_focus(false) {}

    bool has_focus;
};

class EnemyPanel : public Panel {
  public:
    EnemyPanel() {}
    EnemyPanel(ofRectangle bound, int enemy_number)
      : Panel(bound), enemy_number(enemy_number), name(GetRandomEnemyName()), ip(GetRandomIpString()) {}
    EnemyPanel(float x, float y, float width, float height, int enemy_number)
      : Panel(x, y, width, height), enemy_number(enemy_number), name(name), ip(GetRandomIpString()) {}

    std::string name;
    int enemy_number;
    std::string ip;
};

class UtilButton : public Panel {
  public:
    UtilButton() {}
    UtilButton(ofRectangle bound, int row, int column, ofImage *icon) 
      : Panel(bound), row(row), column(column), icon(icon) {}
    UtilButton(float x, float y, float width, float height, int row, int column) 
      : Panel(x, y, width, height), row(row), column() {}
    // ~UtilButton();

    std::string title;
    ofImage *icon;

    int row, column;
};

class ConsolePanel : public Panel {
  public:
    ConsolePanel() {}
    ConsolePanel(ofRectangle bound) : Panel(bound) {}
    ConsolePanel(float x, float y, float width, float height) 
      : Panel(x, y, width, height) {}

    std::vector<std::string> history;
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
const std::vector<std::string> kUtilButtonIconPaths = {"icons/shield.png", "icons/attack_shield.png", "", "",
"", "", "", ""};

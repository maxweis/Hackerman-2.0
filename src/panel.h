#pragma once

#include "ofMain.h"
#include "enemy.h"
#include <vector>

enum UtilButtonType {
  CONNECT, //connect to enemies
  DISCONNECT, //disconnect from enemies
  FIREWALL_UP, //put up firewall
  ENCRYPT, //encrypt your password
  FILESYSTEM, //access your filesystem
  STORE, //purchase upgrades from store
  FIREWALL_ATTACK, //attack enemy's firewall
  DECRYPT //decrypt enemy's password once firewall is down
};

class Panel : public ofRectangle {
  public:
    Panel() : has_focus(false) {}
    Panel(ofRectangle bound) : ofRectangle(bound), has_focus(false),
    background_color(ofColor(0, 0, 0, 255)) {}

    virtual void Focus() { has_focus = !has_focus; }

    bool has_focus;
    ofColor background_color;
};

class EnemyPanel : public Panel {
  public:
    EnemyPanel() {}
    EnemyPanel(ofRectangle bound, int enemy_number)
      : Panel(bound), name(GetRandomEnemyName()), enemy_number(enemy_number),
      ip(GetRandomIpString()) {}

    void Focus() override;

    std::string name;
    int enemy_number;
    std::string ip;
};

class UtilButton : public Panel {
  public:
    UtilButton() {}
    UtilButton(ofRectangle bound, int button_number, int row, int column,
        ofImage *icon) 
      : Panel(bound), icon(icon), number(button_number), row(row), 
      column(column) {}
    // ~UtilButton();

    std::string title;
    ofImage *icon;

    //number int 0-indexed
    int number, row, column;
};

class ConsolePanel : public Panel {
  public:
    ConsolePanel() {}
    ConsolePanel(ofRectangle bound) : Panel(bound), sh_enabled(false) {}

    std::deque<std::string> history;
    std::stringstream current_command;

    //access sh shell
    bool sh_enabled;
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
std::string sh_exec(std::string cmd);

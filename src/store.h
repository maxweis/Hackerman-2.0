#pragma once

#include <iostream>
#include <vector>
#include "ofMain.h"

enum UpgradeType {
  FIREWALL_UPGRADE,
  SH_UPGRADE
};

class Upgrade {
  public:
  Upgrade() {}
  Upgrade(int cost, UpgradeType type) : cost(cost), type(type) {}


  ofImage icon;
  int cost;
  ofRectangle bound;
  UpgradeType type;
};

const std::string kFirewallUpgradeImagePath = "icons/firewall_upgrade.png";
const std::string kShUpgradeImagePath = "icons/sh_upgrade.png" ;

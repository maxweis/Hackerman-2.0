#include "store.h"
#include "ofApp.h"

//load images used in the store
void Hackerman::InitStoreImages() {
  upgrade_images = std::vector<ofImage>(SH_UPGRADE + 1, ofImage());
  float image_size = main_panel.height / (upgrade_images.size() * 2);

  upgrade_images[0].load(kFirewallUpgradeImagePath);
  upgrade_images[1].load(kShUpgradeImagePath);

  upgrade_images[0].resize(image_size, image_size);
  upgrade_images[1].resize(image_size, image_size);
}

//create upgrade objects
void Hackerman::InitUpgrades() {
  upgrades.push_back(Upgrade(3, FIREWALL_UPGRADE));
  upgrades.push_back(Upgrade(5, SH_UPGRADE));

  upgrades[0].icon = upgrade_images[upgrades[0].type];
  upgrades[1].icon = upgrade_images[upgrades[1].type];
}

void Hackerman::OpenStoreInterface() {
  main_panel.state = STORE;
}

void Hackerman::DrawStoreInterface() {
  for (unsigned int i = 0; i < upgrade_images.size(); i++) {
    float y_ratio = (i + 1) / (float) (upgrade_images.size() + 1); 
    ofRectangle icon_bound;
    //draw current amount of money
    font_inconsolata14.DrawTopLeftAlign(std::to_string(player.bitcoin) + " BTC", 
        main_panel, kWhite, kBorderWidth);

    icon_bound = DrawCenterAlignX(upgrade_images[i], (ofRectangle) main_panel,
        y_ratio);

    ofRectangle text_bound = icon_bound;
    int text_offset = upgrade_images[i].getHeight() / 2 + kBorderWidth * 2;
    text_bound.y += text_offset;
    font_inconsolata14.DrawCenterAlign(std::to_string(upgrades[i].cost) + " BTC",
        text_bound, kMainColor);

    upgrades[i].bound = icon_bound;
  }
}

//handle user attempting to buy an upgrade
void Hackerman::BuyUpgrade(UpgradeType type) {
  if (player.bitcoin < upgrades[type].cost) {
    PrintToConsole("You do not have enough bitcoin for this upgrade.");
  } else if (player.bitcoin > upgrades[type].cost) {
    switch (type) {
      case FIREWALL_UPGRADE:
        player.defense++;
        PrintToConsole("A firewall upgrade has been unlocked.");
        player.bitcoin -= upgrades[type].cost;
        break;

      case SH_UPGRADE:
        if (!player.sh_unlocked) {
          player.sh_unlocked = true;
          PrintToConsole("Enhanced terminal has been unlocked. Type 'sh' for access.");
          player.bitcoin -= upgrades[type].cost;
        } else {
          PrintToConsole("You have already acquired this upgrade.");
        }
        break;
    }
  }
}

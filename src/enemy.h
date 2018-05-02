#pragma once

#include <vector>
#include <iostream>
#include "player.h"
#include "ofMain.h"

std::string GetRandomEnemyName();
std::string GetRandomIpString();

const int kEnemyAmount = 5;

const int kEnemyNamesAmount = 18;
const std::string kEnemyNames[] = {"L33T HX0R", "[spunge]", "Left Handed Jimmy", 
"Sam Hammich", "Dr. Moonshine", "Master Mayhem", "hackin-hecker", "artemis_fowl", "cindy southpaw",
"8\"", "bup bup bup", "king jellybean", "flawed_human", "meeseeks", "munk", "lienux",
"dota_john", "gaudy gus"};

class Enemy {
  public:
    Enemy(int enemy_number) : name(GetRandomEnemyName()), password(GetRandomPassword(5)),
        number(enemy_number), bitcoin((int) ofRandom(1, 3)), ip(GetRandomIpString()),
        firewall_up(false), defeated(false) {}

    std::string name;
    std::string password;
    int number;
    int bitcoin;
    std::string ip;
    bool firewall_up;
    bool defeated;
};

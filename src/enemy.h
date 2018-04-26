#pragma once

#include <vector>
#include <iostream>

class Enemy {
  public:
    bool firewall_up;

    bool defeated;
    std::string name;
    int enemy_number;
    std::string ip;
};

const int kEnemyAmount = 5;

const int kEnemyNamesAmount = 18;
const std::string kEnemyNames[] = {"L33T HX0R", "[spunge]", "Left Handed Jimmy", 
"Sam Hammich", "Dr. Moonshine", "Master Mayhem", "hackin-hecker", "artemis_fowl", "cindy southpaw",
"8\"", "bup bup bup", "king jellybean", "flawed_human", "meeseeks", "munk", "lienux",
"dota_john", "gaudy gus"};

std::string GetRandomEnemyName();
std::string GetRandomIpString();

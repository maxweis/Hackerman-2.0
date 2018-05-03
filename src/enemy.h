#pragma once

#include <vector>
#include <iostream>
#include "player.h"
#include "ofMain.h"

std::string GetRandomEnemyName();
std::string GetRandomIpString();

const int kEnemyAmount = 5;

const int kEnemyNamesAmount = 17;
const std::string kEnemyNames[] = {"L33T HX0R", "[spunge]", "Left Handed Jimmy", 
"Sam Hammich", "Dr. Moonshine", "Master Mayhem", "hackin-hecker", "artemis_fowl", "cindy southpaw",
"bup bup bup", "king jellybean", "flawed_human", "meeseeks", "munk", "lienux",
"dota_john", "gaudy gus"};

class Enemy {
  public:
    Enemy() {}
    Enemy(const Enemy &other) : name(other.name), password(other.password),
        number(other.number), bitcoin(other.bitcoin), ip(other.ip),
        firewall_strength(other.firewall_strength), 
        firewall_up(other.firewall_up), firewall_attack_time(other.firewall_attack_time),
        firewall_attacked(other.firewall_attacked), defeated(other.defeated) {}
 
    Enemy(int enemy_number) : name(GetRandomEnemyName()), password(GetRandomPassword(5)),
        number(enemy_number), bitcoin((int) ofRandom(1, 3)), ip(GetRandomIpString()),
        firewall_strength(ofRandom(5, 15)), firewall_up(true), firewall_attack_time(0),
        firewall_attacked(false), defeated(false) {}

    std::string name;
    std::string password;
    int number;
    int bitcoin;
    std::string ip;
    int firewall_strength;
    bool firewall_up;
    //time at which firewall will be down
    float firewall_attack_time;
    bool firewall_attacked;
    bool defeated;
};

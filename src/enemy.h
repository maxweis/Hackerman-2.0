#pragma once

#include <vector>
#include <iostream>

const int kEnemyAmount = 5;

const int kEnemyNamesAmount = 18;
const std::string kEnemyNames[] = {"L33T HX0R", "[spunge]", "Left Handed Jimmy", 
"Sam Hammich", "Dr. Moonshine", "Master Mayhem", "hackin-hecker", "Sombra", "cindy southpaw",
"8\"", "bup bup bup", "king jellybean", "flawed_human", "meeseeks", "munk", "lienux",
"dota_john", "gaudy gus"};

std::string GetRandomEnemyName();
std::string GetRandomIpString();

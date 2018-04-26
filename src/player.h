#include <iostream>

std::string RandomString(int length);

class Player {
  public:
    Player() : bitcoin(0), password(RandomString(10)), connected(false),
    firewall_up(false), attack(1), defense(0){}

    int bitcoin;
    std::string password;

    bool connected;
    bool firewall_up;

    int attack;
    int defense;
};

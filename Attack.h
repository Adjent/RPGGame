#pragma once

class Attack {
private:
    int damage;
    int range;

public:
    Attack(int dmg = 0, int rng = 1);

    int getValue() const; 
    int getRange() const; 
};
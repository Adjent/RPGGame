#pragma once
class Armor {
private:
    int value;
public:
    Armor(int val = 0);
    int reduceDamage(int incomingDamage) const;
    int getValue() const;
    void decrease(int amount);
};
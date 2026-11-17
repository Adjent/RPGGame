#include "Armor.h"
Armor::Armor(int val) : value(val < 0 ? 0 : val) {}
int Armor::reduceDamage(int incomingDamage) const {
    int reduced = incomingDamage * (100 - value) / 100;
    return reduced < 1 ? 1 : reduced;
}
int Armor::getValue() const { return value; }
void Armor::decrease(int amount) { value -= amount; if (value < 0) value = 0; }
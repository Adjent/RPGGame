#include "Attack.h"

Attack::Attack(int dmg, int rng) : damage(dmg), range(rng) {}

int Attack::getValue() const { return damage; }
int Attack::getRange() const { return range; }
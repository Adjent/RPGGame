#include "SwordMeleeUnit.h"

Sword::Sword(int id) : Melee(id, 2) {}

std::string Sword::getType() const {
    return "Swordman";
}

char Sword::getSymbol()const {
    return 'S';
}

Unit* Sword::clone() const {
    return new Sword(*this);
}
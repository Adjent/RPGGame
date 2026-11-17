#include "ArcherRangedUnit.h"

Archer::Archer(int id) : Ranged(id, 5) {}

std::string Archer::getType() const {
    return "Archer";
}

char Archer::getSymbol() const {
    return 'A';
}

Unit* Archer::clone() const {
    return new Archer(*this);
}
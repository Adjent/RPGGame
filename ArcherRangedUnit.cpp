#include "ArcherRangedUnit.h"

Archer::Archer(int id) : Ranged(id, 5) {}

std::string Archer::getType() const {
    return "Archer";
}

char Archer::getSymbol() const {
    return 'A';
}

std::unique_ptr<Unit> Archer::clone() const {
    return std::make_unique<Archer>(*this);
}
#include "MaceTankUnit.h"

Mace::Mace(int id) : Tank(id, 2) {}

std::string Mace::getType() const {
    return "Maceman";
}

char Mace::getSymbol() const {
    return 'M';
}

Unit* Mace::clone() const {
    return new Mace(*this);
}

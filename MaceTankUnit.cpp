#include "MaceTankUnit.h"

Mace::Mace(int id) : Tank(id, 2) {}

std::string Mace::getType() const {
    return "Maceman";
}

char Mace::getSymbol() const {
    return 'M';
}

std::unique_ptr<Unit> Mace::clone() const {
    return std::make_unique<Mace> (*this);
}

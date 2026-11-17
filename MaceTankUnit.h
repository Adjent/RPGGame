#pragma once
#include "TankUnit.h"

class Mace : public Tank {
public:
    Mace(int id);
    Mace(const Mace& other) = default;
    std::string getType() const override;
    char getSymbol() const override;
    Unit* clone() const override;
};
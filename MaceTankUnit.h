#pragma once
#include "TankUnit.h"

class Mace : public Tank {
public:
    Mace(int id);
    Mace(const Mace& other) = default;
    std::string getType() const override;
    char getSymbol() const override;
    std::unique_ptr<Unit> clone() const override;
};
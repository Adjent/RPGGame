#pragma once
#include "TankUnit.h"

class Hammer : public Tank {
public:
    Hammer(int id);
    Hammer(const Hammer& other) = default;
    bool attackTarget(Unit* target, GameField* field) override;
    std::string getType() const override;
    char getSymbol() const override;
    Unit* clone() const override;
};
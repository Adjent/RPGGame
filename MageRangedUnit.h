#pragma once
#include "RangedUnit.h"

class Mage : public Ranged {
public:
    Mage(int id);
    Mage(const Mage& other) = default;
    bool attackTarget(Unit* target, GameField* field) override;
    std::string getType() const override;
    char getSymbol() const override;
    Unit* clone() const override;
};

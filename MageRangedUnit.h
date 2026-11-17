#pragma once
#include "RangedUnit.h"

class Mage : public Ranged {
public:
    Mage(int id);
    Mage(const Mage& other) = default;
    bool attackTarget(Unit* target, GameField* field) override;
    std::string getType() const override;
    char getSymbol() const override;
    std::unique_ptr<Unit> clone() const override;
};

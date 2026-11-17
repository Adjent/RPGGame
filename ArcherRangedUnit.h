#pragma once
#include "RangedUnit.h"

class Archer : public Ranged {
public:
    Archer(int id);
    Archer(const Archer& other) = default;
    std::string getType() const override;
    char getSymbol() const override;
    std::unique_ptr<Unit> clone() const override;
};


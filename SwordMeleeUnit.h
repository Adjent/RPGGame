#pragma once
#include "MeleeUnit.h"

class Sword : public Melee {
public:
    Sword(int id);
    Sword(const Sword& other) = default;
    std::string getType() const override;
    char getSymbol() const override;
    std::unique_ptr<Unit> clone() const override;
};
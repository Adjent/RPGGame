#pragma once
#include "Unit.h"

class Melee : public Unit {
public:
    Melee(int id, int rng);
    Melee(const Melee& other) = default;
};

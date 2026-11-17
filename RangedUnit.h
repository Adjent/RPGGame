#pragma once
#include "Unit.h"

class Ranged : public Unit {
public:
    Ranged(int id, int rng);
    Ranged(const Ranged& other) = default;
};

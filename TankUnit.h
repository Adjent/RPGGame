#pragma once
#include "Unit.h"

class Tank : public Unit {
public:
    Tank(int id, int rng);
    Tank(const Tank& other) = default;
};
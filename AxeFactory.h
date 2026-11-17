#pragma once
#include "MeleeFactory.h"
#include "AxeMeleeUnit.h"

class AxeFactory final : public MeleeFactory {
protected:
    Unit* createRaw(int newId) const override;
};
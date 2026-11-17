#pragma once
#include "MeleeFactory.h"
#include "SwordMeleeUnit.h"

class SwordFactory final : public MeleeFactory {
protected:
    Unit* createRaw(int newId) const override;
};
#pragma once
#include "RangedFactory.h"
#include "MageRangedUnit.h"

class MageFactory final : public RangedFactory {
protected:
    Unit* createRaw(int newId) const override;
};
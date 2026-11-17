#pragma once
#include "RangedFactory.h"
#include "ArcherRangedUnit.h"

class ArcherFactory final : public RangedFactory {
protected:
    Unit* createRaw(int newId) const override;
};
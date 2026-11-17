#pragma once
#include "RangedFactory.h"
#include "ArcherRangedUnit.h"

class ArcherFactory final : public RangedFactory {
protected:
    std::unique_ptr<Unit> createRaw(int newId) const override;
};
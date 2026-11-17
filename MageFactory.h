#pragma once
#include "RangedFactory.h"
#include "MageRangedUnit.h"

class MageFactory final : public RangedFactory {
protected:
	std::unique_ptr<Unit> createRaw(int newId) const override;
};
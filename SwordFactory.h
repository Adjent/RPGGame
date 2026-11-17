#pragma once
#include "MeleeFactory.h"
#include "SwordMeleeUnit.h"

class SwordFactory final : public MeleeFactory {
protected:
	std::unique_ptr<Unit> createRaw(int newId) const override;
};
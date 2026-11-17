#pragma once
#include "TankFactory.h"
#include "HammerTankUnit.h"

class HammerFactory final : public TankFactory {
protected:
	std::unique_ptr<Unit> createRaw(int newId) const override;
};
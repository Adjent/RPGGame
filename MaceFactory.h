#pragma once
#include "TankFactory.h"
#include "MaceTankUnit.h"

class MaceFactory final : public TankFactory {
protected:
	std::unique_ptr<Unit> createRaw(int newId) const override;
};
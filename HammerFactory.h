#pragma once
#include "TankFactory.h"
#include "HammerTankUnit.h"

class HammerFactory final : public TankFactory {
protected:
    Unit* createRaw(int newId) const override;
};
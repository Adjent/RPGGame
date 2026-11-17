#pragma once
#include "TankFactory.h"
#include "MaceTankUnit.h"

class MaceFactory final : public TankFactory {
protected:
    Unit* createRaw(int newId) const override;
};
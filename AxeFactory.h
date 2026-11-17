#pragma once
#include "MeleeFactory.h"
#include "AxeMeleeUnit.h"

class AxeFactory final : public MeleeFactory {
protected:
    std::unique_ptr<Unit> createRaw(int newId) const override;
};
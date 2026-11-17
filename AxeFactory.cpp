#include "AxeFactory.h"

std::unique_ptr<Unit> AxeFactory::createRaw(int newId) const {
    return std::make_unique<Axe>(newId);
}
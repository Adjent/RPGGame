#include "MageFactory.h"

std::unique_ptr<Unit> MageFactory::createRaw(int newId) const {
    return std::make_unique<Mage>(newId);
}
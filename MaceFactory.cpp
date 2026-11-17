#include "MaceFactory.h"

std::unique_ptr<Unit> MaceFactory::createRaw(int newId) const {
    return std::make_unique<Mace>(newId);
}
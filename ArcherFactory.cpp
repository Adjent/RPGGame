#include "ArcherFactory.h"

std::unique_ptr<Unit> ArcherFactory::createRaw(int newId) const {
    return std::make_unique<Archer>(newId);
}
#include "SwordFactory.h"

std::unique_ptr<Unit> SwordFactory::createRaw(int newId) const {
    return std::make_unique<Sword>(newId);
}
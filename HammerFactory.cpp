#include "HammerFactory.h"

std::unique_ptr<Unit> HammerFactory::createRaw(int newId) const {
    return std::make_unique<Hammer>(newId);
}
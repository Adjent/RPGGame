#include "MageFactory.h"

Unit* MageFactory::createRaw(int newId) const {
    return new Mage(newId);
}
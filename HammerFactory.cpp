#include "HammerFactory.h"

Unit* HammerFactory::createRaw(int newId) const {
    return new Hammer(newId);
}
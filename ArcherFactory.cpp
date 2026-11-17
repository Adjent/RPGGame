#include "ArcherFactory.h"

Unit* ArcherFactory::createRaw(int newId) const {
    return new Archer(newId);
}
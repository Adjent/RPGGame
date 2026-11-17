#include "MaceFactory.h"

Unit* MaceFactory::createRaw(int newId) const {
    return new Mace(newId);
}
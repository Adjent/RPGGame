#include "AxeFactory.h"

Unit* AxeFactory::createRaw(int newId) const {
    return new Axe(newId);
}
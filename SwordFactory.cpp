#include "SwordFactory.h"

Unit* SwordFactory::createRaw(int newId) const {
    return new Sword(newId);
}
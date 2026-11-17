#include "MageRangedUnit.h"
#include <iostream>

Mage::Mage(int id) : Ranged(id, 3) {}


bool Mage::attackTarget(Unit* target, GameField* field) {
    if (Ranged::attackTarget(target, field)) {
        if (target && !target->isDead()) {
            std::cout << this->getType() << " #" << this->getId()
                << " cursed " << target->getType()
                << " #" << target->getId() << "!\n";
            target->applyCurse();
        }
        return true; 
    }
    return false; 
}

std::string Mage::getType() const {
    return "Wizrd";
}

char Mage::getSymbol()const {
    return 'W';
}

Unit* Mage::clone() const {
    return new Mage(*this);
}

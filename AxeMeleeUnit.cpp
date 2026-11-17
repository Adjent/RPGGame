#include "AxeMeleeUnit.h"
#include <iostream>

Axe::Axe(int id) : Melee(id, 1) {} 

bool Axe::attackTarget(Unit* target, GameField* field) {
    if (Melee::attackTarget(target, field)) {
        if (target && !target->isDead() && !target->getBleedingStatus()) {
            std::cout << "Bleeding! " << target->getType() << "'s armor decrease by 3.\n";
            target->reduceArmor(5);
            target->applyBleeding();
        }
        return true;
    }
    return false;
}

std::string Axe::getType() const {
    return "Viking";
}

char Axe::getSymbol() const {
    return 'V';
}

Unit* Axe::clone() const {
    return new Axe(*this);
}
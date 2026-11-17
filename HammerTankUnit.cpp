#include "HammerTankUnit.h"
#include <iostream>
#include <cstdlib> 

Hammer::Hammer(int id) : Tank(id, 1) {}

bool Hammer::attackTarget(Unit* target, GameField* field) {
    if (Tank::attackTarget(target, field)) {
        if (target && !target->isDead()) {
            if (rand() % 100 < 25) {
                std::cout << target->getType() << " stunned! Double damage!\n";
                Tank::attackTarget(target, field);
            }
        }
        return true;
    }
    return false;
}

std::string Hammer::getType() const {
    return "Hammerman";
}

char Hammer::getSymbol()const {
    return 'H';
}

std::unique_ptr<Unit> Hammer::clone() const {
    return std::make_unique<Hammer>(*this);
}
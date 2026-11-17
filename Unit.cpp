#include "Unit.h"
#include "GameField.h"
#include <cmath>


Unit::Unit(int id, int h, int a, int atkDmg, int atkRange) : id(id), health(h), armor(a), attack(atkDmg, atkRange), isCursed(false), isBleeding(false) {
}

void Unit::reduceArmor(int amount) {
    armor.decrease(amount);
}

bool Unit::attackTarget(Unit* target, GameField* field) {

    if (!target || target->isDead()) return false;
    int distance = std::abs(field->getX(this) - field->getX(target)) +
        std::abs(field->getY(this) - field->getY(target));

    if (distance > attack.getRange()) {
        std::cout << getType() << " #" << id << " can't hit " << target->getType()
            << " #" << target->getId() << " too far (Current distance: "
            << distance << ", Max range: " << attack.getRange() << ")\n";
        return false; 
    }
    int finalDmg = target->armor.reduceDamage(attack.getValue());
    std::cout << getType() << " #" << id << " hit " << target->getType() << " #" << target->getId()
        << " for " << finalDmg << " damage!\n";

    target->takeDamage(finalDmg);
    return true; 
}


void Unit::takeDamage(int rawDamage) {
    if (isCursed) {
        std::cout << "Cursed " << getType() << " #" << id << " took 5 extra damage!\n";
        rawDamage += 5;
        isCursed = false;
    }

    health.decrease(rawDamage);

    if (isDead()) {
        std::cout << getType() << " #" << id << " died\n";
    }
}

void Unit::printInfo() const {
    std::cout << getType() << " #" << id
        << " [HP: " << health.getValue()
        << ", Armor: " << armor.getValue()
        << ", Attack: " << attack.getValue()
        << ", AttackRange: " << attack.getRange() << "]\n";
}

bool Unit::move(GameField* field, int newX, int newY) {
    if (!field) return false;
    if (isDead()) return false;

    if (newX < 0 || newX >= field->getWidth() || newY < 0 || newY >= field->getHeight()) {
        return false;
    }

    if (field->getUnitAt(newX, newY) != nullptr)return false;
    field->updatePosition(this, newX, newY);
    return true;
}
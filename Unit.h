#pragma once
#include "Health.h"
#include "Attack.h"
#include "Armor.h"
#include <string>
#include <iostream>

class GameField;

class Unit {
private:
    int id;

protected:
    Health health;
    Armor armor;
    Attack attack;
    bool isCursed; 
    bool isBleeding;

public:
    Unit(int id, int h, int a, int atkDmg, int atkRange);
    virtual ~Unit() = default;

    int getRange() const { return attack.getRange(); }
    int getId() const { return id; }
    int getHealthValue() const { return health.getValue(); }
    int getArmorValue() const { return armor.getValue(); }
    int getAttackValue() const { return attack.getValue(); }
    bool getBleedingStatus() const { return isBleeding; }

    void setId(int newId) { id = newId; }

    bool isDead() const { return health.isZero(); }
    void applyCurse() { isCursed = true; }
    void applyBleeding() { isBleeding = true; }
    void reduceArmor(int amount);

    virtual bool move(GameField* field, int newX, int newY);
    virtual bool attackTarget(Unit* target, GameField* field);
    virtual void takeDamage(int rawDamage);

    virtual Unit* clone() const = 0;
    virtual std::string getType() const = 0;
    virtual char getSymbol() const = 0;
    virtual void printInfo() const;
};
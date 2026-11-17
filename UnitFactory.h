#pragma once
#include "Unit.h"

class UnitFactory {
protected:
    virtual Unit* createRaw(int newId) const = 0;

public:
    virtual ~UnitFactory() = default;

    Unit* create() const {
        static int nextId = 1;
        return createRaw(nextId++);
    }
};
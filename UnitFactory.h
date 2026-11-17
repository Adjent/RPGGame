#pragma once
#include <memory>
#include "Unit.h"

class UnitFactory {
protected:
    virtual std::unique_ptr<Unit> createRaw(int newId) const = 0;

public:
    virtual ~UnitFactory() = default;

    std::unique_ptr<Unit> create() const {
        static int nextId = 1;
        return createRaw(nextId++);
    }
};
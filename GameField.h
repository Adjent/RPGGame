#pragma once
#include "Unit.h"
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <memory>

class UnitFactory;

class GameField {
private:
    std::vector<std::unique_ptr<Unit>> units;
    std::vector<std::vector<Unit*>> grid;
    std::map<Unit*, std::pair<int, int>> positions;

    int width;
    int height;
    int maxUnits;
    int currentUnitsCount;

    void clear();
    void copyFrom(const GameField& other);

public:
    GameField(int w, int h, int maxU);
    ~GameField();

    GameField(const GameField& other);
    GameField& operator=(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(GameField&& other) noexcept;

    bool addUnit(std::unique_ptr<Unit> unit, int x, int y);
    void removeUnit(Unit* unit);
    void updatePosition(Unit* unit, int newX, int newY);
    bool isEmpty() const;

    int getUnitsCount() const;
    int getWidth() const;
    int getHeight() const;
    int getX(Unit* unit) const;
    int getY(Unit* unit) const;
    int getmaxUnits() const;
    Unit* getUnitAt(int x, int y) const;

    void printField() const;
    void printAllUnitsInfo() const;
    void removeDeadUnits();
    void populate(UnitFactory* factory, int count);


    class Iterator {
    private:
        const GameField* field;
        int curX, curY;
        void findNext();

    public:
        Iterator(const GameField* f, int x, int y);
        bool operator!=(const Iterator& other) const;
        void operator++();
        Unit* operator*() const;
    };

    Iterator begin() const;
    Iterator end() const;
};
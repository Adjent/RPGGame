#include "GameField.h"
#include "UnitFactory.h"
#include <cstdlib>
#include <stdexcept>


GameField::GameField(int w, int h, int maxU)
    : width(w), height(h), maxUnits(maxU), currentUnitsCount(0) {
    grid.resize(height, std::vector<Unit*>(width, nullptr));
}

GameField::~GameField() {
    clear();
}

void GameField::clear() {
    positions.clear();
    grid.clear();
    units.clear();
    currentUnitsCount = 0;
}

void GameField::copyFrom(const GameField& other) {
    width = other.width;
    height = other.height;
    maxUnits = other.maxUnits;
    currentUnitsCount = 0;
    grid.resize(height, std::vector<Unit*>(width, nullptr));

    for (const auto& pair : other.positions) {
        Unit* originalUnit = pair.first;
        int x = pair.second.first;
        int y = pair.second.second;
        std::unique_ptr<Unit> clonedUnit = originalUnit->clone();
        if (!addUnit(std::move(clonedUnit), x, y)) {
            throw std::runtime_error("Failed to copy unit");
        }
    }
}

GameField::GameField(const GameField& other) {
    copyFrom(other);
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

GameField::GameField(GameField&& other) noexcept
    : units(std::move(other.units)),
    grid(std::move(other.grid)),
    positions(std::move(other.positions)),
    width(other.width),
    height(other.height),
    maxUnits(other.maxUnits),
    currentUnitsCount(other.currentUnitsCount) {

    other.units.clear();
    other.grid.clear();
    other.positions.clear();
    other.width = 0;
    other.height = 0;
    other.maxUnits = 0;
    other.currentUnitsCount = 0;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        clear();
        units = std::move(other.units);
        grid = std::move(other.grid);
        positions = std::move(other.positions);
        width = other.width;
        height = other.height;
        maxUnits = other.maxUnits;
        currentUnitsCount = other.currentUnitsCount;

        other.units.clear();
        other.grid.clear();
        other.positions.clear();
        other.width = 0;
        other.height = 0;
        other.maxUnits = 0;
        other.currentUnitsCount = 0;
    }
    return *this;
}

void GameField::printField() const {
    for (int x = 0; x < width + 2; ++x) std::cout << "X ";
    std::cout << "\n";

    for (int y = 0; y < height; ++y) {
        std::cout << "X ";
        for (int x = 0; x < width; ++x) {
            if (grid[y][x] == nullptr) {
                std::cout << "  ";
            }
            else {
                if (grid[y][x]->getId() == 1) {
                    std::cout << "U ";
                }
                else {
                    std::cout << grid[y][x]->getSymbol() << " ";
                }
            }
        }
        std::cout << "X\n";
    }
    for (int x = 0; x < width + 2; ++x) std::cout << "X ";
}

bool GameField::addUnit(std::unique_ptr<Unit> unit, int x, int y) {
    if (!unit || x < 0 || x >= width || y < 0 || y >= height)
        return false;
    if (currentUnitsCount >= maxUnits || grid[y][x] != nullptr)
        return false;

    Unit* rawUnit = unit.get();
    grid[y][x] = rawUnit;
    positions[rawUnit] = { x, y };
    units.push_back(std::move(unit));
    currentUnitsCount++;
    return true;
}

void GameField::removeUnit(Unit* unit) {
    auto it = positions.find(unit);

    if (it != positions.end()) {
        int x = it->second.first;
        int y = it->second.second;

        grid[y][x] = nullptr;
        positions.erase(it);

        for (auto ownerIt = units.begin(); ownerIt != units.end(); ++ownerIt) {
            if (ownerIt->get() == unit) {
                units.erase(ownerIt);
                break;
            }
        }

        currentUnitsCount--;
    }
}

void GameField::updatePosition(Unit* unit, int newX, int newY) {
    auto it = positions.find(unit);

    if (it == positions.end()) return;

    if (newX < 0 || newX >= width || newY < 0 || newY >= height)
        return;

    if (grid[newY][newX] != nullptr)
        return;

    int oldX = it->second.first;
    int oldY = it->second.second;

    grid[oldY][oldX] = nullptr;
    grid[newY][newX] = unit;

    it->second = { newX, newY };
}

int GameField::getUnitsCount()const {
    return currentUnitsCount;
}

int GameField::getHeight()const {
    return height;
}

int GameField::getWidth()const {
    return width;
}

int GameField::getmaxUnits()const {
    return maxUnits;
}

int GameField::getX(Unit* unit) const {
    auto it = positions.find(unit);
    return (it != positions.end()) ? it->second.first : -1;
}

int GameField::getY(Unit* unit) const {
    auto it = positions.find(unit);
    return (it != positions.end()) ? it->second.second : -1;
}

Unit* GameField::getUnitAt(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) return nullptr;
    return grid[y][x];
}

bool GameField::isEmpty() const {
    return currentUnitsCount == 0;
}

GameField::Iterator::Iterator(const GameField* f, int x, int y)
    : field(f), curX(x), curY(y) {
    findNext();
}

bool GameField::Iterator::operator!=(const Iterator& other) const {
    return field != other.field || curX != other.curX || curY != other.curY;
}

void GameField::Iterator::findNext() {
    while (curY < field->height) {
        if (curX >= field->width) {
            curX = 0;
            curY++;
            continue;
        }
        if (field->grid[curY][curX] != nullptr) return;
        curX++;
    }
}

void GameField::Iterator::operator++() {
    curX++;
    findNext();
}

Unit* GameField::Iterator::operator*() const {
    return field->grid[curY][curX];
}

GameField::Iterator GameField::begin() const {
    return Iterator(this, 0, 0);
}

GameField::Iterator GameField::end() const {
    return Iterator(this, 0, height);
}

void GameField::printAllUnitsInfo() const {
    std::cout << "All units on the field:\n";
    int count = 0;

    for (const Unit* u : *this) {
        u->printInfo();
        count++;
    }

    if (count == 0) {
        std::cout << "No units on the field.\n";
    }
    else {
        std::cout << "Total units: " << count << "\n";
    }
}

void GameField::removeDeadUnits() {
    std::vector<Unit*> deadUnits;

    for (Unit* u : *this) {
        if (u->isDead()) {
            deadUnits.push_back(u);
        }
    }

    for (Unit* dead : deadUnits) {
        removeUnit(dead);
    }
}

void GameField::populate(UnitFactory* factory, int count) {
    if (!factory || width <= 0 || height <= 0 || count <= 0)
        return;

    int placed = 0;
    int attempts = 0;
    int maxAttempts = width * height * 2;

    while (placed < count && attempts < maxAttempts) {
        int randX = rand() % width;
        int randY = rand() % height;

        if (grid[randY][randX] == nullptr) {
            std::unique_ptr<Unit> newUnit = factory->create();

            if (addUnit(std::move(newUnit), randX, randY)) {
                placed++;
            }
        }

        attempts++;
    }
}
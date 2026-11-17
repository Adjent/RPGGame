#include <iostream>
#include <windows.h>
#include <limits>
#include <string>
#include <vector>
#include <ctime> 
#include <memory>
#include <utility>

#include "GameField.h"
#include "HammerFactory.h"
#include "MaceFactory.h"
#include "SwordFactory.h"
#include "AxeFactory.h"
#include "ArcherFactory.h"
#include "MageFactory.h"

using namespace std;

void clearScreen() {
    system("cls");
}

int getValidInput(int min, int max) {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter a number (" << min << "-" << max << "): ";
        }
        else if (value < min || value > max) {
            cout << "Invalid choice! Enter a number (" << min << "-" << max << "): ";
            cin.ignore(10000, '\n');
        }
        else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}


void testCopy(const vector<UnitFactory*>& factories) {
    cout << "\n<<< COPY TEST >>>\n";

    GameField original(10, 10, 10);

    auto attacker = factories[2]->create();
    auto target = factories[0]->create();

    if (!original.addUnit(std::move(attacker), 4, 4)) {
        cout << "Failed to create attacker!\n";
        return;
    }

    if (!original.addUnit(std::move(target), 5, 4)) {
        cout << "Failed to create target!\n";
        return;
    }

    cout << "\nOriginal field:\n";
    original.printField();
    cout << "\n";
    original.printAllUnitsInfo();

    GameField copy(original);

    Unit* originalAttacker = original.getUnitAt(4, 4);
    Unit* originalTarget = original.getUnitAt(5, 4);
    Unit* copiedAttacker = copy.getUnitAt(4, 4);
    Unit* copiedTarget = copy.getUnitAt(5, 4);

    cout << "\n<<< Pointer comparison >>>\n"
        << "Original attacker: " << originalAttacker << "\n"
        << "Copied attacker:   " << copiedAttacker << "\n"
        << "Original target:   " << originalTarget << "\n"
        << "Copied target:     " << copiedTarget << "\n";

    bool differentPointers =
        originalAttacker != copiedAttacker &&
        originalTarget != copiedTarget;

    cout << "\nDifferent pointers: "
        << (differentPointers ? "PASS" : "FAIL") << "\n"
        << "\nAttack copied target\n";

    int originalHP = originalTarget->getHealthValue();
    int copiedHP = copiedTarget->getHealthValue();

    bool copyAttack = copiedAttacker->attackTarget(copiedTarget, &copy);

    cout << "Original target HP: " << originalTarget->getHealthValue() << "\n"
        << "Copied target HP: " << copiedTarget->getHealthValue() << "\n";

    bool firstCheck =
        copyAttack &&
        originalTarget->getHealthValue() == originalHP;

    cout << "Original unchanged: "
        << (firstCheck ? "PASS" : "FAIL") << "\n"
        << "\nAttack original target\n";

    copiedHP = copiedTarget->getHealthValue();

    bool originalAttack =
        originalAttacker->attackTarget(originalTarget, &original);

    cout << "Original target HP: " << originalTarget->getHealthValue() << "\n"
        << "Copied target HP: " << copiedTarget->getHealthValue() << "\n";

    bool secondCheck =
        originalAttack &&
        copiedTarget->getHealthValue() == copiedHP;

    cout << "Copy unchanged: "
        << (secondCheck ? "PASS" : "FAIL") << "\n"
        << "\n<<< COPY TEST FINISHED >>>\n";
}

void testMove(const vector<UnitFactory*>& factories) {
    cout << "\n<<< MOVE TEST >>>\n";

    GameField source(10, 10, 10);

    for (int i = 0; i < 3; i++) {
        auto unit = factories[i]->create();

        if (!source.addUnit(std::move(unit), 3 + i, 3)) {
            cout << "Failed to add unit!\n";
        }
    }

    int unitsBeforeMove = source.getUnitsCount();

    cout << "Units before move: " << unitsBeforeMove << "\n";

    GameField destination(std::move(source));

    cout << "\nAfter move constructor:\n";
    cout << "Destination units: "
        << destination.getUnitsCount() << "\n";

    bool constructorCheck =
        destination.getUnitsCount() == unitsBeforeMove;

    cout << "Move constructor: "
        << (constructorCheck ? "PASS" : "FAIL") << "\n";

    GameField anotherField(5, 5, 10);

    anotherField = std::move(destination);

    cout << "\nAfter move assignment:\n";
    cout << "New destination units: "
        << anotherField.getUnitsCount() << "\n";

    bool assignmentCheck =
        anotherField.getUnitsCount() == unitsBeforeMove;

    cout << "Move assignment: "
        << (assignmentCheck ? "PASS" : "FAIL") << "\n";

    cout << "\n<<< MOVE TEST FINISHED >>>\n";
}


void testIterator(const vector<UnitFactory*>& factories) {
    cout << "\n<<<ITERATOR TEST >>>\n";

    GameField field(10, 10, 10);

    for (int i = 0; i < 3; i++) {
        auto unit = factories[i]->create();

        if (!field.addUnit(std::move(unit), 2 + i, 2)) {
            cout << "Failed to add unit!\n";
        }
    }

    cout << "\n<<< Occupied elements >>>\n";

    int visited = 0;

    for (Unit* unit : field) {
        if (unit == nullptr) {
            cout << "FAIL: nullptr found!\n";
            return;
        }

        unit->printInfo();
        visited++;
    }

    cout << "Visited: " << visited << "\n"
        << "Occupied iteration: "
        << (visited == field.getUnitsCount() ? "PASS" : "FAIL") << "\n"
        << "\n<<< Empty container >>>\n";

    GameField emptyField(5, 5, 10);

    int emptyCount = 0;

    for (Unit* unit : emptyField) {
        emptyCount++;
    }

    cout << "Empty iteration: "
        << (emptyCount == 0 && emptyField.isEmpty() ? "PASS" : "FAIL") << "\n"
        << "\n<<< Independent iterators >>>\n";

    auto it1 = field.begin();
    auto it2 = field.begin();

    Unit* firstUnit = *it2;
    ++it1;

    cout << "Independent iterators: "
        << (*it2 == firstUnit ? "PASS" : "FAIL") << "\n"
        << "\n<<< Deletion during iteration >>>\n";

    int deleted = 0;
    auto it = field.begin();

    while (it != field.end()) {
        Unit* current = *it;
        ++it;
        field.removeUnit(current);
        deleted++;
    }

    cout << "Deleted units: " << deleted << "\n"
        << "Field empty after deletion: "
        << (field.isEmpty() ? "PASS" : "FAIL") << "\n"
        << "\n<<< ITERATOR TEST FINISHED >>>\n";
}

void testMenu(const vector<UnitFactory*>& factories) {
    while (true) {
        clearScreen();
        cout << "<<< GAMEFIELD TESTS >>>\n\n"\
            << "1. Copy and deep copy test\n"\
            << "2. Move field test\n"\
            << "3. Iterator test\n"\
            << "4. Run all tests\n"\
            << "0. Back\n"\
            << "\nChoice: ";

        int choice = getValidInput(0, 4);

        if (choice == 0) {
            return;
        }
        clearScreen();
        switch (choice) {
        case 1:
            testCopy(factories);
            break;
        case 2:
            testMove(factories);
            break;
        case 3:
            testIterator(factories);
            break;
        case 4:
            testCopy(factories);
            testMove(factories);
            testIterator(factories);
            break;
        }

        cout << "\nPress Enter to return...";
        cin.get();
    }
}

void startGame(const vector<UnitFactory*>& factories, const int fieldW, const int fieldH,const int unitCnt) {
    GameField field(fieldW, fieldH, unitCnt);
    int centerX = fieldW / 2;
    int centerY = fieldH / 2;
    //create character
    int classChoice;
    while (true) {
        clearScreen();
        cout << "<<< WELCOME TO THE GAME >>>\n\n"\
            "1. Hammerman\n"\
            "2. Maceman\n"\
            "3. Swordman\n"\
            "4. Viking\n"\
            "5. Archer\n"\
            "6. Wizrd\n"\
            "0. Exit game\n\n"\
            "Select class (0-6): ";

        classChoice = getValidInput(0, 6);
        if (classChoice == 0) return;
        break;
    }

    auto playerUnit = factories[classChoice - 1]->create();
    if (!field.addUnit(std::move(playerUnit), centerX, centerY)) {
        cout << "Failed to create player!\n";
        cin.get();
        return;
    }
    Unit* player = field.getUnitAt(centerX, centerY);

    cout << "\nCharacter created successfully! Press Enter...";
    cin.get();

    //enemies spawn
    int enemiesCount = 1;
    cout << "\nEnter the number of enemies: ";
    enemiesCount = getValidInput(1, field.getmaxUnits());
    for (int i = 0; i < enemiesCount; ++i) {
        int randomFactoryIndex = rand() % factories.size();
        field.populate(factories[randomFactoryIndex], 1);
    }

    cout << "\nEnemies have been spawned on the map! Press Enter...";
    cin.get();

    //game cycle 
    while (true) {
        if (player->isDead()) {
            clearScreen(); cout << "<<< GAME OVER >>>\nYou died!\n"; break;
        }
        bool enemiesLeft = false;
        for (Unit* u : field) { if (u != player) enemiesLeft = true; }
        if (!enemiesLeft) {
            clearScreen(); cout << "<<< VICTORY >>>\nYou won!\n"; break;
        }

        //player turn
        clearScreen();
        cout << "<<< YOUR TURN >>>\nYour hero: " << player->getType() << "\n";

        field.printField();
        cout << "\n1. Up | 2. Down | 3. Left | 4. Right\n5. Attack in radius | 6. Show all units info | 0. Exit game\nChoice: ";

        int choice = getValidInput(0, 6);

        if (choice == 0) {
            clearScreen(); cout << "Exit the game.\n"; break;
        }

        int px = field.getX(player);
        int py = field.getY(player);
        int nx = px, ny = py;

        bool actionTaken = true;

        switch (choice) {
        case 1: ny--; break;
        case 2: ny++; break;
        case 3: nx--; break;
        case 4: nx++; break;
        case 5: {
            //attack
            vector<Unit*> targets;
            for (Unit* u : field) {
                if (u->getId() != player->getId() && !u->isDead()) {
                    int dist = abs(px - field.getX(u)) + abs(py - field.getY(u));
                    if (dist <= player->getRange()) targets.push_back(u);
                }
            }

            if (targets.empty()) {
                cout << "\nNo targets in range!\nPress Enter...";
                cin.get();
                actionTaken = false;
            }
            else if (targets.size() == 1) {
                cout << "\nAttacked: "; targets[0]->printInfo();
                player->attackTarget(targets[0], &field);
                cout << "Result -> Target " << targets[0]->getType() \
                    << "#" << targets[0]->getId()\
                    << " has HP: " << targets[0]->getHealthValue()\
                    << ", Armor: " << targets[0]->getArmorValue() << "\n";
                cin.get();
            }
            else {
                cout << "\nEnemies in range:\n";
                for (size_t i = 0; i < targets.size(); ++i) {
                    cout << i + 1 << ". "; targets[i]->printInfo();
                }
                cout << "Select target (1-" << targets.size() << "): ";
                int tChoice = getValidInput(1, targets.size());
                player->attackTarget(targets[tChoice - 1], &field);
                cin.get();
            }
            break;
        }
        case 6: {
            clearScreen();
            cout << "\nYour hero : " << player->getType() << "\n";
            field.printField();
            field.printAllUnitsInfo();
            cout << "\nPress Enter to return to the menu...";
            cin.get();
            actionTaken = false;
            break;
        }
        }
        if (!actionTaken) continue;
        if (choice >= 1 && choice <= 4) {
            if (!player->move(&field, nx, ny)) {
                cout << "Blocked! (wall or occupied)\n";
                cin.get();
            }
        }

        field.removeDeadUnits();

        //enemies turn
        vector<string> enemyLogs;

        vector<Unit*> enemies;
        for (Unit* u : field) {
            if (u->getId() != player->getId() && !u->isDead()) {
                enemies.push_back(u);
            }
        }
        for (Unit* enemy : enemies) {
            if (enemy->isDead()) continue;
            if (player->isDead()) break;

            int currentPx = field.getX(player);
            int currentPy = field.getY(player);

            int ex = field.getX(enemy);
            int ey = field.getY(enemy);
            int distToPlayer = abs(ex - currentPx) + abs(ey - currentPy);

            if (distToPlayer <= enemy->getRange() && (rand() % 100 < 50)) {//enemies attacked player in 50%
                enemy->attackTarget(player, &field);
                string logMsg = enemy->getType() + "#" + to_string(enemy->getId()) + " Attacks you! ";
                logMsg += "(Your HP: " + to_string(player->getHealthValue()) + ", Armor: " + to_string(player->getArmorValue()) + ")";
                enemyLogs.push_back(logMsg);
            }
            else {
                int dx[] = { 0, 0, -1, 1 };
                int dy[] = { -1, 1, 0, 0 };
                string dirNames[] = { "up", "down", "left", "right" };

                int dir = rand() % 4;
                int enx = ex + dx[dir];
                int eny = ey + dy[dir];

                string logMsg = enemy->getType() + "#" + to_string(enemy->getId()) + " move " + dirNames[dir];

                if (enemy->move(&field, enx, eny)) {
                    enemyLogs.push_back(logMsg + " (Success)");
                }
                else {
                    enemyLogs.push_back(logMsg + " (Blocked)");
                }
            }
        }

        //enemies combat log output
        clearScreen();
        cout << "<<< ENEMY TURN RESULT >>>\n";
        field.printField();

        cout << "\nCombat log:\n";
        for (const string& log : enemyLogs) {
            cout << log << "\n";
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));
    const int fieldW = 21;
    const int fieldH = 21;
    const int unitCnt = 10;

    HammerFactory  f1;
    MaceFactory    f2;
    SwordFactory   f3;
    AxeFactory     f4;
    ArcherFactory  f5;
    MageFactory    f6;
    vector<UnitFactory*> factories = { &f1, &f2, &f3, &f4, &f5, &f6 };

    while (true) {
        clearScreen();
        cout << "<<< WELCOME >>>\n\n";
        cout << "1. Start game\n";
        cout << "2. Tests menu\n";
        cout << "0. Exit\n";
        cout << "\nChoice: ";

        int choice = getValidInput(0, 2);
        switch (choice) {
        case 1:
        {
            startGame(factories, fieldW, fieldH, unitCnt);
            break;
        }
        case 2:
            testMenu(factories);
            break;
        case 0:
            return 0;
        }
    }
    
    return 0;
}
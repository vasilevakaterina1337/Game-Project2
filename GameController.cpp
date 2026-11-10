#include "GameController.h"
#include <iostream>
#include <limits>
#include "Terrain.h"
#include "NeutralObject.h"

int readInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minVal && value <= maxVal) return value;
        std::cout << "Ошибка ввода\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

GameController::GameController() : base_(0, 0, 1000, 5), field_(10, 10), isRunning_(true) {
    field_.setTerrain(5, 5, new Mountains());
    field_.setTerrain(2, 2, new Forest());
}

void GameController::run() {
    while (isRunning_) {
        field_.printField(base_.getUnits());

        std::cout << "\nГлавное меню\n"
            << "1. Создать юнита\n"
            << "2. Установить ландшафт\n"
            << "3. Установить нейтрала\n"
            << "4. Нанести урон (Наблюдатель)\n"
            << "0. Выход\n";

        int choice = readInt("Выбор: ", 0, 4);

        if (choice == 1) {
            int t = readInt("Тип (1-Пехота, 2-Лучник, 3-Маг, 4-Летун): ", 1, 4);
            int x = readInt("X: ", 0, 9);
            int y = readInt("Y: ", 0, 9);
            UnitType type = (t == 1) ? UnitType::INFANTRY : (t == 2) ? UnitType::ARCHER : (t == 3) ? UnitType::MAGE : UnitType::FLYING;
            base_.createUnit(type, x, y);
        }
        else if (choice == 2) {
            std::cout << "1. Равнина\n2. Лес\n3. Горы\n4. Болото\n";
            int t = readInt("Тип ландшафта: ", 1, 4);
            int x = readInt("X: ", 0, 9);
            int y = readInt("Y: ", 0, 9);

            if (t == 1) field_.setTerrain(x, y, new Plains());
            else if (t == 2) field_.setTerrain(x, y, new Forest());
            else if (t == 3) field_.setTerrain(x, y, new Mountains());
            else if (t == 4) field_.setTerrain(x, y, new Swamp());
        }
        else if (choice == 3) {
            std::cout << "1. Сундук (лечит)\n2. Ловушка (урон)\n3. Алтарь (бафф)\n4. Источник (хил)\n";
            int o = readInt("Тип объекта: ", 1, 4);
            int x = readInt("X: ", 0, 9);
            int y = readInt("Y: ", 0, 9);

            if (o == 1) field_.setNeutral(x, y, new TreasureChest());
            else if (o == 2) field_.setNeutral(x, y, new Trap());
            else if (o == 3) field_.setNeutral(x, y, new Altar());
            else if (o == 4) field_.setNeutral(x, y, new EnergySource());
        }
        else if (choice == 4) {
            if (!base_.getUnits().empty()) {
                std::cout << "Наносим 150 урона первому юниту...\n";
                base_.getUnits()[0]->takeDamage(150);
            }
            else {
                std::cout << "Нет юнитов для атаки!\n";
            }
        }
        else if (choice == 0) {
            isRunning_ = false;
        }
    }
}
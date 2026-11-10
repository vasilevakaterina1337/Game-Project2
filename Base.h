#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Unit.h"
#include "Observer.h"
#include "UnitFactory.h"

class Base : public IObserver {
    int health_, maxUnits_, defenseLevel_, resources_;
    int x_, y_;
    std::vector<std::shared_ptr<Unit>> units_;

public:
    Base(int x, int y, int hp, int maxU)
        : x_(x), y_(y), health_(hp), maxUnits_(maxU), defenseLevel_(10), resources_(100) {
    }
    int getX() const { 
        return x_; 
    }
    int getY() const { 
        return y_; 
    }
    const std::vector<std::shared_ptr<Unit>>& getUnits() const { 
        return units_; 
    }
    void createUnit(UnitType type, int x, int y) {
        if (units_.size() >= (size_t)maxUnits_) { 
            std::cout << "База переполнена\n"; 
        return; 
        }
        static DefaultUnitFactory factory;
        auto newUnit = factory.createUnit(type, x, y);
        units_.push_back(newUnit);
        newUnit->subscribe(this);
        newUnit->notify({ UnitEventType::CREATED, newUnit.get(), 0 });
    }

    void onUnitEvent(const UnitEvent& event) override {
        if (event.type == UnitEventType::DESTROYED) {
            std::cout << "Юнит " << event.unit->getName() << " уничтожен. Список обновлен\n";

            units_.erase(std::remove_if(units_.begin(), units_.end(),
                [&event](const std::shared_ptr<Unit>& u) {
                    return u.get() == event.unit;
                }), units_.end());

        }
        else if (event.type == UnitEventType::DAMAGED) {
            std::cout << "Юнит " << event.unit->getName() << " получил урон: " << event.damage << "\n";
        }
    }
};
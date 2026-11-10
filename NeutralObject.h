#pragma once
#include <memory>
#include <iostream>
#include "Strategy.h"
#include "Unit.h"

class NeutralObject {
protected:
    std::unique_ptr<IInteractionStrategy> strategy_;
public:
    NeutralObject(std::unique_ptr<IInteractionStrategy> strat) : strategy_(std::move(strat)) {}
    virtual ~NeutralObject() = default;
    virtual void interact(Unit& unit) { 
        if (strategy_) 
            strategy_->apply(unit); 
    }
};

class TreasureChest : public NeutralObject {
public:
    TreasureChest() : NeutralObject(std::make_unique<HealthRestoreStrategy>()) {}
};

class Trap : public NeutralObject {
public:
    Trap() : NeutralObject(nullptr) {}
    void interact(Unit& unit) override { 
        unit.takeDamage(30); std::cout << unit.getName() << " наступил на ловушку\n"; 
}
};

class Altar : public NeutralObject {
public:
    Altar() : NeutralObject(nullptr) {}
    void interact(Unit& unit) override {
        if (unit.getType() == UnitType::MAGE) 
            strategy_ = std::make_unique<HealthRestoreStrategy>();
        else 
            strategy_ = std::make_unique<AttackBoostStrategy>();
        strategy_->apply(unit);
    }
};

class EnergySource : public NeutralObject {
public:
    EnergySource() : NeutralObject(nullptr) {}
    void interact(Unit& unit) override { 
        unit.heal(1000); 
        std::cout << unit.getName() << " восстановил здоровье\n"; 
    }
};

inline Unit& operator+(Unit& unit, TreasureChest& obj) { 
    obj.interact(unit); 
    return unit; 
}
inline Unit& operator-(Unit& unit, Trap& obj) { 
    obj.interact(unit); 
    return unit; 
}
inline Unit& operator*(Unit& unit, Altar& obj) { 
    obj.interact(unit); 
    return unit; 
}
inline Unit& operator/(Unit& unit, EnergySource& obj) { 
    obj.interact(unit); 
    return unit; 
}
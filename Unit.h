#pragma once
#include <string>
#include <memory>
#include "Attributes.h"
#include "Observer.h"
#include "Types.h"

class Unit : public IObservable {
protected:
    static int next_id_;
    int id_;
    int x_, y_;
    Health health_;
    Armor armor_;
    Attack attack_;
    std::string name_;
    UnitType type_;

public:
    Unit(int x, int y, std::string name, UnitType type, int hp, int armor, int attack);
    virtual ~Unit() = default;

    int getId() const {
        return id_;
    }
    int getX() const { 
        return x_;
    }
    int getY() const { 
        return y_;
    }
    UnitType getType() const { 
        return type_;
    }
    std::string getName() const {
        return name_;
    }
    Attack& getAttack() {
        return attack_;
    }

    void move(int new_x, int new_y) {
        x_ = new_x; y_ = new_y;
    }
    void takeDamage(int amount);
    void heal(int amount) { 
        health_.increase(amount);
    }
    void attackUnit(Unit& target);
};

class Infantry : public Unit {
public:
    Infantry(int x, int y) : Unit(x, y, "Пехотинец", UnitType::INFANTRY, 100, 10, 15) {}
};

class Archer : public Unit {
public:
    Archer(int x, int y) : Unit(x, y, "Лучник", UnitType::ARCHER, 80, 5, 20) {}
};

class Mage : public Unit {
public:
    Mage(int x, int y) : Unit(x, y, "Маг", UnitType::MAGE, 60, 5, 30) {}
};

class FlyingUnit : public Unit {
public:
    FlyingUnit(int x, int y) : Unit(x, y, "Летун", UnitType::FLYING, 70, 5, 25) {}
};
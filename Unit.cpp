#include "Unit.h"
#include <iostream>

int Unit::next_id_ = 1;

Unit::Unit(int x, int y, std::string name, UnitType type, int hp, int armor, int attack)
    : id_(next_id_++), x_(x), y_(y), name_(std::move(name)), type_(type),
    health_(hp), armor_(armor), attack_(attack)
{
}

void Unit::takeDamage(int amount) {
    health_.decrease(armor_.reduceDamage(amount));
    notify({ UnitEventType::DAMAGED, this, amount });
    if (health_.isZero()) notify({ UnitEventType::DESTROYED, this, 0 });
}

void Unit::attackUnit(Unit& target) {
    std::cout << name_ << " атакует " << target.getName() << "\n";
    target.takeDamage(attack_.getValue());
}
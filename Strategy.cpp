#include "Strategy.h"
#include "Unit.h"
#include <iostream>

void AttackBoostStrategy::apply(Unit& unit) {
    unit.getAttack().increase(10);
    std::cout << unit.getName() << " получает +10 к атаке\n";
}
void HealthRestoreStrategy::apply(Unit& unit) {
    unit.heal(50);
    std::cout << unit.getName() << " восстанавливает 50 HP\n";
}
#include "UnitFactory.h"

std::shared_ptr<Unit> DefaultUnitFactory::createUnit(UnitType type, int x, int y) const {
    switch (type) {
    case UnitType::INFANTRY: 
        return std::make_shared<Infantry>(x, y);
    case UnitType::ARCHER:   
        return std::make_shared<Archer>(x, y);
    case UnitType::MAGE:     
        return std::make_shared<Mage>(x, y);
    case UnitType::FLYING:   
        return std::make_shared<FlyingUnit>(x, y);
    default: 
        throw std::invalid_argument("Неизвестный тип");
    }
}
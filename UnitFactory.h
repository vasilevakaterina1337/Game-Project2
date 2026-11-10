#pragma once
#include <memory>
#include "Unit.h"

class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    virtual std::shared_ptr<Unit> createUnit(UnitType type, int x, int y) const = 0;
};

class DefaultUnitFactory : public UnitFactory {
public:
    std::shared_ptr<Unit> createUnit(UnitType type, int x, int y) const override;
};
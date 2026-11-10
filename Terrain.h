#pragma once
#include "Types.h"
#include <string>
#include <iostream>

class Terrain {
public:
    virtual ~Terrain() = default;
    virtual bool isPassable(UnitType type) const = 0;
    virtual double getSpeedModifier(UnitType type) const = 0;
    virtual double getDefenseBonus(UnitType type) const = 0;
    virtual std::string getName() const = 0;
};

class Plains : public Terrain {
public:
    bool isPassable(UnitType) const override { 
        return true; 
    }
    double getSpeedModifier(UnitType) const override { 
        return 1.0; 
    }
    double getDefenseBonus(UnitType) const override { 
        return 0.0;
    }
    std::string getName() const override { 
        return "Равнина"; 
    }
};

class Forest : public Terrain {
public:
    bool isPassable(UnitType type) const override { 
        return type != UnitType::MAGE; 
    }
    double getSpeedModifier(UnitType type) const override { 
        return type == UnitType::INFANTRY ? 0.5 : 0.8; 
    }
    double getDefenseBonus(UnitType) const override { 
        return 5.0;
    }
    std::string getName() const override { 
        return "Лес"; 
    }
};

class Swamp : public Terrain {
public:
    bool isPassable(UnitType type) const override { 
        return type != UnitType::MAGE; 
    }
    double getSpeedModifier(UnitType) const override { 
        return 0.5; 
    }
    double getDefenseBonus(UnitType) const override { 
        return 0.0; 
    }
    std::string getName() const override { 
        return "Болото";
    }
};

class Mountains : public Terrain {
public:
    bool isPassable(UnitType type) const override { 
        return type == UnitType::FLYING; 
    }
    double getSpeedModifier(UnitType) const override {
        return 0.5; 
    }
    double getDefenseBonus(UnitType) const override { 
        return 10.0; 
    }
    std::string getName() const override { 
        return "Горы"; 
    }
};

class TerrainProxy : public Terrain {
    Terrain* realTerrain_;
public:
    TerrainProxy(Terrain* t) : realTerrain_(t) {}
    ~TerrainProxy() override { 
        delete realTerrain_; 
    }
    bool isPassable(UnitType type) const override { 
        return type == UnitType::FLYING ? true : realTerrain_->isPassable(type); 
    }
    double getSpeedModifier(UnitType type) const override { 
        return realTerrain_->getSpeedModifier(type); 
    }
    double getDefenseBonus(UnitType type) const override { 
        return realTerrain_->getDefenseBonus(type); 
    }
    std::string getName() const override {
        return realTerrain_->getName() + " (Прокси)";
    }
};
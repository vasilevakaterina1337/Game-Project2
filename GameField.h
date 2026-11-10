#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Unit.h"
#include "Terrain.h"
#include "NeutralObject.h"

class GameField {
    int width_, height_;
    std::vector<std::vector<std::shared_ptr<Terrain>>> terrainMap_;
    std::vector<std::vector<std::shared_ptr<NeutralObject>>> neutralMap_;
public:
    GameField(int w, int h) : width_(w), height_(h) {
        for (int i = 0; i < w; ++i) {
            std::vector<std::shared_ptr<Terrain>> rowT;
            std::vector<std::shared_ptr<NeutralObject>> rowN;
            for (int j = 0; j < h; ++j) {
                rowT.push_back(std::make_shared<TerrainProxy>(new Plains()));
                rowN.push_back(nullptr);
            }
            terrainMap_.push_back(rowT);
            neutralMap_.push_back(rowN);
        }
    }
    void setTerrain(int x, int y, Terrain* t) {
        terrainMap_[x][y] = std::make_shared<TerrainProxy>(t); 
    }
    void setNeutral(int x, int y, NeutralObject* obj) { 
        neutralMap_[x][y] = std::shared_ptr<NeutralObject>(obj); 
    }
    bool moveUnit(const std::shared_ptr<Unit>& unit, int newX, int newY) {
        if (!terrainMap_[newX][newY]->isPassable(unit->getType())) {
            std::cout << "Проход заблокирован (" << terrainMap_[newX][newY]->getName() << ")\n";
            return false;
        }
        unit->move(newX, newY);
        return true;
    }
    void interactWithNeutral(const std::shared_ptr<Unit>& unit, int x, int y) {
        if (neutralMap_[x][y]) {
            if (auto* trap = dynamic_cast<Trap*>(neutralMap_[x][y].get())) 
                *unit - *trap;
            else if (auto* chest = dynamic_cast<TreasureChest*>(neutralMap_[x][y].get())) 
                *unit + *chest;
            else if (auto* altar = dynamic_cast<Altar*>(neutralMap_[x][y].get())) 
                *unit** altar;
            else if (auto* source = dynamic_cast<EnergySource*>(neutralMap_[x][y].get())) 
                *unit / *source;
            neutralMap_[x][y] = nullptr;
        }
    }
    void printField(const std::vector<std::shared_ptr<Unit>>& units) const {
        std::cout << "\n   ";
        for (int x = 0; x < width_; ++x) 
            std::cout << x << " ";
        std::cout << "\n";
        for (int y = 0; y < height_; ++y) {
            std::cout << y << "| ";
            for (int x = 0; x < width_; ++x) {
                bool unitDrawn = false;
                for (const auto& u : units) {
                    if (u->getX() == x && u->getY() == y) {
                        if (u->getType() == UnitType::INFANTRY) 
                            std::cout << "I ";
                        else if (u->getType() == UnitType::ARCHER) 
                            std::cout << "A ";
                        else if (u->getType() == UnitType::MAGE) 
                            std::cout << "M ";
                        else if (u->getType() == UnitType::FLYING) 
                            std::cout << "F ";
                        unitDrawn = true; break;
                    }
                }
                if (unitDrawn) 
                    continue;
                if (neutralMap_[x][y]) {
                    if (dynamic_cast<TreasureChest*>(neutralMap_[x][y].get())) 
                        std::cout << "$ ";
                    else if (dynamic_cast<Trap*>(neutralMap_[x][y].get())) 
                        std::cout << "x ";
                    else if (dynamic_cast<Altar*>(neutralMap_[x][y].get())) 
                        std::cout << "A ";
                    else if (dynamic_cast<EnergySource*>(neutralMap_[x][y].get())) 
                        std::cout << "E ";
                }
                else {
                    std::string tName = terrainMap_[x][y]->getName();
                    if (tName.find("Равнина") != std::string::npos) 
                        std::cout << ". ";
                    else if (tName.find("Лес") != std::string::npos) 
                        std::cout << "* ";
                    else if (tName.find("Горы") != std::string::npos) 
                        std::cout << "^ ";
                    else if (tName.find("Болото") != std::string::npos) 
                        std::cout << "~ ";
                }
            }
            std::cout << "\n";
        }
    }
};
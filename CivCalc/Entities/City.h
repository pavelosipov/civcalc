//
//  City.h
//  CivCalc
//
//  Created by Pavel Osipov on 01.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "Goods.h"
#include "CityBuilding.h"

#include <deque>
#include <memory>
#include <vector>
#include <queue>

class ActionQueue;
class Building;
class City;
class Granary;
class Tile;

class CityTurnLogger {
public:
    void addEvent(const std::string &eventName);
    void addWhipEvent(uint8_t whipCount);
    void setGoods(const Goods &goods);
    void logTurn(uint8_t turn, const City &city);
    
private:
    Goods goods_;
    Goods goodsChange_;
    std::deque<std::string> events_;
};

class City {
public:
    City();
    
    uint8_t population() const;
    void setPopulation(uint8_t population);
    int16_t nextPopulationFood() const;
    
    uint8_t happiness() const;
    void setHappiness(uint8_t happiness);
    
    uint8_t unhappiness() const;
    void setUnhappiness(uint8_t unhappiness);
    
    const Goods &accumulatedGoods() const;
    void setAccumulatedGoods(const Goods &goods);
    
    std::shared_ptr<Building> topBuilding() const;
    void setTopBuilding(std::shared_ptr<Building> building);
    void pushBuilding(std::shared_ptr<Building> building);
    void swapBuildings(size_t lpos, size_t rpos);
    
    void addCityBuilding(std::shared_ptr<CityBuilding> building);
    
    std::shared_ptr<Tile> tileAt(size_t index) const;
    void setTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void swapTiles(size_t lpos, size_t rpos);
    void removeTile(std::shared_ptr<Tile> tile);
    
    void chop();
    
    bool canWhip() const;
    void whip();
    
    void processBuildingQueue(uint8_t initialTurn, ActionQueue &actionQueue);
    
    CityTurnLogger &turnLogger() const;
    
private:
    uint8_t workingTilesCount() const;
    Goods workTiles() const;
    void produceBuilding(Goods &goods);
    void applyCityBuildings(Goods &goods);
    void grow(Goods &goods);
    
public:
    friend CityTurnLogger;
    friend std::ostream& operator << (std::ostream &stream, const City &city);
    
private:
    uint8_t population_;
    uint8_t happiness_;
    Goods accumulatedGoods_;
    typedef std::vector<std::shared_ptr<Tile>> TileSet;
    TileSet tiles_;
    typedef std::deque<std::shared_ptr<Building>> BuildingQueue;
    BuildingQueue buildingQueue_;
    std::queue<uint8_t> whipTurns_;
    std::unique_ptr<CityTurnLogger> turnLogger_;
    typedef std::deque<std::shared_ptr<CityBuilding>> CityBuildings;
    CityBuildings cityBuildings_;
};

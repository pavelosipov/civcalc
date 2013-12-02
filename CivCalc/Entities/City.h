//
//  City.h
//  CivCalc
//
//  Created by Pavel Osipov on 01.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "Goods.h"

#include <deque>
#include <memory>
#include <vector>
#include <queue>

class ActionQueue;
class Building;
class City;
class Tile;

class CityTurnLogger {
public:
    void addEvent(const std::string &eventName);
    void addWhipEvent(uint8_t whipCount);
    void setGoods(const Goods &goods);
    void logTurn(uint8_t turn, const City &city);
    
private:
    Goods goods_;
    std::deque<std::string> events_;
};

class City {
public:
    City();
    
    uint8_t population() const;
    void setPopulation(uint8_t population);
    
    uint8_t happiness() const;
    void setHappiness(uint8_t happiness);
    
    uint8_t unhappiness() const;
    void setUnhappiness(uint8_t unhappiness);
    
    const Goods &accumulatedGoods() const;
    void setAccumulatedGoods(const Goods &goods);
    
    std::shared_ptr<Building> topBuilding() const;
    void setTopBuilding(std::shared_ptr<Building> building);
    void pushBuilding(std::shared_ptr<Building> building);
    
    void setTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void insertTile(uint8_t position, std::shared_ptr<Tile> tile);
    void removeTile(std::shared_ptr<Tile> tile);
    
    bool canWhip() const;
    void whip();
    
    void processBuildingQueue(uint8_t initialTurn, ActionQueue &actionQueue);
    
    CityTurnLogger &turnLogger() const;
    
private:
    Goods workTiles() const;
    void produceBuilding(Goods &goods);
    void grow(Goods &goods);
    
public:
    friend CityTurnLogger;
    friend std::ostream& operator << (std::ostream &stream, const City &city);
    
private:
    uint8_t population_;
    uint8_t happiness_;
    uint8_t unhappiness_;
    Goods accumulatedGoods_;
    std::vector<std::shared_ptr<Tile>> tiles_;
    typedef std::deque<std::shared_ptr<Building>> BuildingQueue;
    BuildingQueue buildingQueue_;
    std::queue<uint8_t> whipTurns_;
    std::unique_ptr<CityTurnLogger> turnLogger_;
};

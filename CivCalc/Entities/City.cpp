//
//  City.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 01.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "City.h"
#include "ActionQueue.h"
#include "Building.h"
#include "Tile.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

City::City()
    : population_(1)
    , happiness_(4)
    , unhappiness_(1)
    , tiles_({Tile::create(2, 1, 1)})
{}

uint8_t City::population() const {
    return population_;
}

void City::setPopulation(uint8_t population) {
    population_ = population;
}

uint8_t City::happiness() const {
    return happiness_;
}

void City::setHappiness(uint8_t happiness) {
    happiness_ = happiness;
}

uint8_t City::unhappiness() const {
    return happiness_;
}

void City::setUnhappiness(uint8_t unhappiness) {
    unhappiness_ = unhappiness;
}

const Goods &City::accumulatedGoods() const {
    return accumulatedGoods_;
}

void City::setAccumulatedGoods(const Goods &goods) {
    accumulatedGoods_ = goods;
}

std::shared_ptr<Building> City::topBuilding() const {
    if (buildingQueue_.empty()) {
        return std::shared_ptr<Building>();
    }
    return buildingQueue_.front();
}

void City::setTopBuilding(std::shared_ptr<Building> building) {
    BuildingQueue::iterator buildingIt = std::find(buildingQueue_.begin(), buildingQueue_.end(), building);
    if (buildingIt == buildingQueue_.end()) {
        buildingQueue_.push_front(building);
    } else {
        buildingIt->swap(*buildingQueue_.begin());
    }
}

void City::pushBuilding(std::shared_ptr<Building> building) {
    buildingQueue_.push_back(building);
}

void City::setTiles(const std::vector<std::shared_ptr<Tile>> &tiles) {
    tiles_.assign(tiles.begin(), tiles.end());
}

void City::insertTile(uint8_t position, std::shared_ptr<Tile> tile) {
    
}

void City::removeTile(std::shared_ptr<Tile> tile) {
    
}

bool City::canWhip() const {
    return false;
}

void City::whip() {
    
}
             
void City::processBuildingQueue(uint8_t turn, ActionQueue &actionQueue) {
    while (!buildingQueue_.empty()) {
        turnLogger_ = std::move(std::unique_ptr<CityTurnLogger>(new CityTurnLogger()));
        Goods turnGoods = workTiles();
        turnLogger_->setGoods(turnGoods);
        actionQueue.applyActions(turn, *this, turnGoods);
        turnLogger_->logTurn(turn, *this);
        turnGoods.hammers += accumulatedGoods_.hammers;
        accumulatedGoods_.hammers = 0;
        produceBuilding(turnGoods);
        grow(turnGoods);
        accumulatedGoods_ += turnGoods;
        ++turn;
    }
}

Goods City::workTiles() const {
    const uint8_t workingTilesCount = std::max(0, population_ - std::max(0, unhappiness_ - happiness_) + 1);
    Goods turnGoods;
    for (int i = 0; i < workingTilesCount; ++i) {
        turnGoods += tiles_[i]->goods();
    }
    turnGoods.food -= 2 * population_;
    return turnGoods;
}

void City::produceBuilding(Goods &goods) {
    if (!buildingQueue_.empty() && buildingQueue_.front()->isComleted()) {
        buildingQueue_.pop_front();
    }
    if (!buildingQueue_.empty()) {
        buildingQueue_.front()->applyGoods(goods);
    }
}

void City::grow(Goods &goods) {
    accumulatedGoods_.food += goods.food;
    goods.food = 0;
    const int8_t nextPopulationFood = 20 + 2 * population_;
    if (accumulatedGoods_.food >= nextPopulationFood) {
        accumulatedGoods_.food -= nextPopulationFood;
        ++population_;
    }
}

CityTurnLogger &City::turnLogger() const {
    return *turnLogger_;
}

void CityTurnLogger::addEvent(const std::string &eventName) {
    events_.push_back(eventName);
}

void CityTurnLogger::setGoods(const Goods &goods) {
    goods_ = goods;
}

void CityTurnLogger::logTurn(uint8_t turn, const City &city) {
    std::cout << std::setfill('0');
    std::cout << "T" << std::setw(2) << static_cast<int>(turn) << ":    "
              << city << "    "
              << goods_ << "    ";
    if (std::shared_ptr<Building> topBuilding = city.topBuilding()) {
        std::cout << *topBuilding << (topBuilding->isComleted() ? "*   " : "    ");
    }
    for (int i = 0; i < events_.size(); ++i) {
        std::cout << events_[i];
    }
    std::cout << std::endl;
}
    
std::ostream& operator << (std::ostream &stream, const City &city) {
    stream << std::setw(2) << static_cast<int>(city.population()) << "    " << city.accumulatedGoods();
    return stream;
}

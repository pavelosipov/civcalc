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

#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>

static const int16_t WhipHammersCount = 30;
static const int16_t ChopHammersCount = 20;

City::City()
    : population_(1)
    , happiness_(4)
    , tiles_({Tile::create(2, 1, 1)})
    , turnLogger_(new CityTurnLogger())
{}

uint8_t City::population() const {
    return population_;
}

void City::setPopulation(uint8_t population) {
    population_ = population;
}

int16_t City::nextPopulationFood() const {
    return 20 + 2 * population_;
}

uint8_t City::happiness() const {
    return happiness_;
}

void City::setHappiness(uint8_t happiness) {
    happiness_ = happiness;
}

uint8_t City::unhappiness() const {
    return population_;
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

void City::swapBuildings(size_t lpos, size_t rpos) {
    assert(lpos < buildingQueue_.size() && rpos < buildingQueue_.size());
    std::swap(buildingQueue_[lpos], buildingQueue_[rpos]);
}

void City::addCityBuilding(std::shared_ptr<CityBuilding> building) {
    cityBuildings_.push_back(building);
}

std::shared_ptr<Tile> City::tileAt(size_t index) const {
    assert(index < tiles_.size());
    return tiles_[index];
}

void City::setTiles(const std::vector<std::shared_ptr<Tile>> &tiles) {
    tiles_.assign(tiles.begin(), tiles.end());
}

void City::swapTiles(size_t lpos, size_t rpos) {
    assert(lpos < tiles_.size() && rpos < tiles_.size());
    std::swap(tiles_[lpos], tiles_[rpos]);
}

void City::removeTile(std::shared_ptr<Tile> tile) {
    
}

void City::chop() {
    turnLogger().addEvent("CHOP");
    accumulatedGoods_.hammers += ChopHammersCount;
}

bool City::canWhip() const {
    if (std::shared_ptr<Building> topBuilding = buildingQueue_.front()) {
        const int16_t whippingHammers = topBuilding->requiredHammers() - topBuilding->accumulatedHammers();
        return 0 < whippingHammers && whippingHammers <= (population_ - 1) * WhipHammersCount;
    }
    return false;
}

void City::whip() {
    assert(canWhip());
    std::shared_ptr<Building> topBuilding = buildingQueue_.front();
    const int16_t whippingHammers = topBuilding->requiredHammers() - topBuilding->accumulatedHammers();
    const uint8_t populationCost = whippingHammers / WhipHammersCount + (whippingHammers % WhipHammersCount ? 1 : 0);
    population_ -= populationCost;
    accumulatedGoods_.hammers += populationCost * WhipHammersCount;
    turnLogger().addWhipEvent(populationCost);
}

void City::processBuildingQueue(uint8_t turn, ActionQueue &actionQueue) {
    while (!buildingQueue_.empty()) {
        Goods turnGoods;
        actionQueue.applyActions(turn, *this, turnGoods);
        turnGoods += workTiles();
        turnLogger_->setGoods(turnGoods);
        turnLogger_->logTurn(turn, *this);
        turnGoods.hammers += accumulatedGoods_.hammers;
        accumulatedGoods_.hammers = 0;
        produceBuilding(turnGoods);
        grow(turnGoods);
        accumulatedGoods_ += turnGoods;
        ++turn;
    }
}

uint8_t City::workingTilesCount() const {
    return std::max(0, population_ - std::max(0, unhappiness() - happiness_) + 1);
}

Goods City::workTiles() const {
    const uint8_t tilesCount = workingTilesCount();
    Goods turnGoods;
    for (int i = 0; i < tilesCount; ++i) {
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
        Building *current
        buildingQueue_.front()->consumeGoods(goods);
        if (
    }
}

void City::grow(Goods &goods) {
    accumulatedGoods_.food += goods.food;
    goods.food = 0;
    const int16_t growFood = nextPopulationFood();
    if (accumulatedGoods_.food >= growFood) {
        accumulatedGoods_.food -= growFood;
        ++population_;
    }
}

CityTurnLogger &City::turnLogger() const {
    return *turnLogger_;
}

void CityTurnLogger::addEvent(const std::string &eventName) {
    events_.push_back(eventName);
}


void CityTurnLogger::addWhipEvent(uint8_t whipCount) {
    char buffer[16];
    sprintf(buffer, "WHIP (%d)", whipCount);
    addEvent(buffer);
}

void CityTurnLogger::setGoods(const Goods &goods) {
    goodsChange_ = goods - goods_;
    goods_ = goods;
}

void CityTurnLogger::logTurn(uint8_t turn, const City &city) {
    std::cout << std::setfill('0');
    std::cout << "T" << std::setw(2) << static_cast<int>(turn) << ":    "
              << city << "    "
              << goods_ << "    ";
    for (int i = 0; i < city.buildingQueue_.size(); ++i) {
        if (i == 0 || city.buildingQueue_[i]->accumulatedHammers() > 0) {
            std::cout << *city.buildingQueue_[i] << (city.buildingQueue_[i]->isComleted() ? "*   " : "    ");
        }
    }
    for (int i = 0; i < events_.size(); ++i) {
        std::cout << events_[i] << "    ";
    }
    events_.clear();
    if (!goodsChange_.isZero()) {
        std::cout << std::setfill(' ');
        std::cout << "±FPС: " << goodsChange_.food << "/" << goodsChange_.hammers << "/" << goodsChange_.commerce;
        goodsChange_ = Goods();
    }
    std::cout << std::endl;
}
    
std::ostream& operator << (std::ostream &stream, const City &city) {
    stream << std::setw(2) << static_cast<int>(city.population()) << "    " << city.accumulatedGoods();
    return stream;
}

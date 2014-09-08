//
//  Building.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 24.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Building.h"
#include "Goods.h"
#include "Granary.h"
#include <iomanip>
#include <string>

Building::Building(const std::string &name, bool eatsFood, int16_t requiredHammers, int16_t accumulatedHammers)
    : name_(name)
    , requiredHammers_(requiredHammers)
    , accumulatedHammers_(accumulatedHammers)
    , buildMultiplier_(1.0f)
    , eatsFood_(eatsFood)
{}

Building::Building(Building &&other)
    : name_(std::move(other.name_))
    , requiredHammers_(other.requiredHammers_)
    , accumulatedHammers_(other.accumulatedHammers_)
    , buildMultiplier_(1.0f)
    , eatsFood_(other.eatsFood_)
{}

Building::~Building()
{}

const std::string &Building::name() const {
    return name_;
}

bool Building::isComleted() const {
    return requiredHammers_ == accumulatedHammers_;
}

int16_t Building::requiredHammers() const {
    return requiredHammers_;
}

int16_t Building::leftHammers() const {
    return (requiredHammers_ - accumulatedHammers_) / buildMultiplier_;
}

int16_t Building::accumulatedHammers() const {
    return accumulatedHammers_;
}

void Building::setAccumulatedHammers(int16_t hammers) {
    accumulatedHammers_ = hammers;
}

int16_t Building::buildMultiplier() const {
    return buildMultiplier_;
}

void Building::setBuildMultiplier(float multiplier) {
    buildMultiplier_ = multiplier;
}

void Building::consumeGoods(City &city, Goods &goods) {
    int16_t consumedHammers = goods.hammers;
    goods.hammers = 0;
    if (eatsFood_) {
        consumedHammers += goods.food;
        goods.food = 0;
    }
    accumulatedHammers_ += buildMultiplier_ * consumedHammers;
    if (accumulatedHammers_ > requiredHammers_) {
        goods.hammers = (accumulatedHammers_ - requiredHammers_) / buildMultiplier_;
        accumulatedHammers_ = requiredHammers_;
    }
}

std::ostream& operator << (std::ostream &stream, const Building &building) {
    stream << building.name_ << " ("
           << std::setw(3) << static_cast<int>(building.accumulatedHammers_) << "/"
           << std::setw(3) << static_cast<int>(building.requiredHammers_) << ")";
    return stream;
}

std::shared_ptr<Building> Building::create(
    const std::string &name,
    bool eatsFood,
    int16_t requiredHammers,
    int16_t accumulatedHammers) {
    return std::make_shared<Building>(name, eatsFood, requiredHammers, accumulatedHammers);
}

std::shared_ptr<Building> Building::galley(int16_t accumulatedHammers) {
    return Building::create("GALLEY    ", false, 50, accumulatedHammers);
}

std::shared_ptr<Building> Building::archer(int16_t accumulatedHammers) {
    return Building::create("ARCHER    ", false, 25, accumulatedHammers);
}

std::shared_ptr<Building> Building::warrior(int16_t accumulatedHammers) {
    return Building::create("WARRIOR   ", false, 15, accumulatedHammers);
}

std::shared_ptr<Building> Building::workBoat(int16_t accumulatedHammers) {
    return Building::create("WORK BOAT ", false, 30, accumulatedHammers);
}

std::shared_ptr<Building> Building::axeman(int16_t accumulatedHammers) {
    return Building::create("AXEMAN    ", false, 35, accumulatedHammers);
}

std::shared_ptr<Building> Building::spearman(int16_t accumulatedHammers) {
    return Building::create("SPEARMAN  ", false, 35, accumulatedHammers);
}

std::shared_ptr<Building> Building::chariot(int16_t accumulatedHammers) {
    return Building::create("CHARIOT   ", false, 25, accumulatedHammers);
}

std::shared_ptr<Building> Building::settler(int16_t accumulatedHammers) {
    return Building::create("SETTLER   ", true,  100, accumulatedHammers);
}

std::shared_ptr<Building> Building::worker(int16_t accumulatedHammers) {
    return Building::create("WORKER    ", true,  60, accumulatedHammers);
}

std::shared_ptr<Building> Building::barracks(int16_t accumulatedHammers) {
    std::shared_ptr<Building> barracks = Building::create("BARRACKS  ", false,  50, accumulatedHammers);
    barracks->setBuildMultiplier(2.0f);
    return barracks;
}

std::shared_ptr<Building> Building::granary(int16_t accumulatedHammers) {
    return std::make_shared<Granary>(accumulatedHammers);
}

std::shared_ptr<Building> Building::lighthouse(int16_t accumulatedHammers) {
    return Building::create("LIGHTHOUSE", false,  60, accumulatedHammers);
}

std::shared_ptr<Building> Building::library(int16_t accumulatedHammers) {
    return Building::create("LIBRARY   ", false,  90, accumulatedHammers);
}

std::shared_ptr<Building> Building::stonehenge(int16_t accumulatedHammers) {
    std::shared_ptr<Building> building = Building::create("STONEHENGE", false,  100, accumulatedHammers);
    building->setBuildMultiplier(1.5f);
    return building;
}

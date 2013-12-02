//
//  Building.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 24.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Building.h"
#include "Goods.h"
#include <iomanip>
#include <string>

Building::Building(const std::string &name, bool eatsFood, int8_t requiredHammers, int8_t accumulatedHammers)
    : name_(name)
    , requiredHammers_(requiredHammers)
    , accumulatedHammers_(accumulatedHammers)
    , eatsFood_(eatsFood)
{}

Building::Building(Building &&other)
    : name_(std::move(other.name_))
    , requiredHammers_(other.requiredHammers_)
    , accumulatedHammers_(other.accumulatedHammers_)
    , eatsFood_(other.eatsFood_)
{}

bool Building::isComleted() const {
    return requiredHammers_ == accumulatedHammers_;
}

int8_t Building::requiredHammers() const {
    return requiredHammers_;
}

int8_t Building::accumulatedHammers() const {
    return accumulatedHammers_;
}

void Building::setAccumulatedHammers(int8_t hammers) {
    accumulatedHammers_ = hammers;
}

void Building::applyGoods(Goods &goods) {
    uint8_t consumedHammers = goods.hammers;
    goods.hammers = 0;
    if (eatsFood_) {
        consumedHammers += goods.food;
        goods.food = 0;
    }
    accumulatedHammers_ += consumedHammers;
    if (accumulatedHammers_ > requiredHammers_) {
        goods.hammers = accumulatedHammers_ - requiredHammers_;
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
    int8_t requiredHammers,
    int8_t accumulatedHammers) {
    return std::make_shared<Building>(name, eatsFood, requiredHammers, accumulatedHammers);
}

std::shared_ptr<Building> Building::warrior(int8_t accumulatedHammers) {
    return Building::create("WARRIOR  ", false, 15, accumulatedHammers);
}

std::shared_ptr<Building> Building::workBoat(int8_t accumulatedHammers) {
    return Building::create("WORK BOAT", false, 30, accumulatedHammers);
}

std::shared_ptr<Building> Building::settler(int8_t accumulatedHammers) {
    return Building::create("SETTLER  ", true,  100, accumulatedHammers);
}

std::shared_ptr<Building> Building::worker(int8_t accumulatedHammers) {
    return Building::create("WORKER   ", true,  60, accumulatedHammers);
}

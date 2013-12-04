//
//  Building.h
//  CivCalc
//
//  Created by Pavel Osipov on 24.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include <string>
#include <memory>

class Goods;

class Building {
public:
    Building(
        const std::string &name,
        bool eatsFood,
        int16_t requiredHammers,
        int16_t accumulatedHammers);
    Building(Building &&other);
    Building(const Building &other) = delete;
    Building &operator = (const Building &other) = delete;
    
    int16_t requiredHammers() const;
    
    int16_t accumulatedHammers() const;
    void setAccumulatedHammers(int16_t hammers);

    bool isComleted() const;
    void applyGoods(Goods &goods);
    
    friend std::ostream& operator << (std::ostream &stream, const Building &building);
    
public:
    static std::shared_ptr<Building> create(
        const std::string &name,
        bool eatsFood,
        int16_t requiredHammers,
        int16_t accumulatedHammers = 0);
    static std::shared_ptr<Building> warrior(int16_t accumulatedHammers = 0);
    static std::shared_ptr<Building> workBoat(int16_t accumulatedHammers = 0);
    static std::shared_ptr<Building> settler(int16_t accumulatedHammers = 0);
    static std::shared_ptr<Building> worker(int16_t accumulatedHammers = 0);
    static std::shared_ptr<Building> axeman(int16_t accumulatedHammers = 0);
    static std::shared_ptr<Building> chariot(int16_t accumulatedHammers = 0);

private:
    const std::string name_;
    const int16_t requiredHammers_;
    int16_t accumulatedHammers_;
    const bool eatsFood_;
};
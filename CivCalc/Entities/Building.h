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
        int8_t requiredHammers,
        int8_t accumulatedHammers);
    Building(Building &&other);
    Building(const Building &other) = delete;
    Building &operator = (const Building &other) = delete;
    
    int8_t requiredHammers() const;
    
    int8_t accumulatedHammers() const;
    void setAccumulatedHammers(int8_t hammers);

    bool isComleted() const;
    void applyGoods(Goods &goods);
    
    friend std::ostream& operator << (std::ostream &stream, const Building &building);
    
public:
    static std::shared_ptr<Building> create(
        const std::string &name,
        bool eatsFood,
        int8_t requiredHammers,
        int8_t accumulatedHammers = 0);
    static std::shared_ptr<Building> warrior(int8_t accumulatedHammers = 0);
    static std::shared_ptr<Building> workBoat(int8_t accumulatedHammers = 0);
    static std::shared_ptr<Building> settler(int8_t accumulatedHammers = 0);
    static std::shared_ptr<Building> worker(int8_t accumulatedHammers = 0);

private:
    const std::string name_;
    const int8_t requiredHammers_;
    int8_t accumulatedHammers_;
    const bool eatsFood_;
};

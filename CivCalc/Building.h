//
//  Building.h
//  CivCalc
//
//  Created by Pavel Osipov on 24.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "Goods.h"
#include <string>

class Building {
public:
    Building(const std::string &name, uint8_t requiredHammers, bool eatsFood)
        : name_(name)
        , requiredHammers_(requiredHammers)
        , accumulatedHammers_(0)
        , eatsFood_(eatsFood)
    {}
    
    bool isComleted() const {
        return requiredHammers_ == accumulatedHammers_;
    }
    
    uint8_t accumulatedHammers() const          { return accumulatedHammers_; }
    void setAccumulatedHammers(uint8_t hammers) { accumulatedHammers_ = hammers; }
    
    void applyGoods(Goods &goods) {
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
    
    friend std::ostream& operator << (std::ostream &stream, const Building &building) {
        stream << building.name_ << " ("
               << std::setw(3) << static_cast<int>(building.accumulatedHammers_) << "/"
               << std::setw(3) << static_cast<int>(building.requiredHammers_) << ")";
        return stream;
    }
    
private:
    const std::string name_;
    const uint8_t requiredHammers_;
    uint8_t accumulatedHammers_;
    const bool eatsFood_;
};

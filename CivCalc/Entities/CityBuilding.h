//
//  CityBuilding.h
//  CivCalc
//
//  Created by Pavel Osipov on 14.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "Building.h"

class City;
class Goods;

class CityBuilding : public Building {
public:
    CityBuilding(
        const std::string &name,
        bool eatsFood,
        int16_t requiredHammers,
        int16_t accumulatedHammers);
    
public: // Building
    virtual void consumeGoods(City &city, Goods &goods);
    
public: // City events
    virtual void processTurnGoods(City &city, Goods &turnGoods);
    virtual void processCityGrowth(City &city);
};
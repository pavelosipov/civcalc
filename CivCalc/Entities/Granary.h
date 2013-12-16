//
//  Granary.h
//  CivCalc
//
//  Created by Pavel Osipov on 14.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "CityBuilding.h"
#include <inttypes.h>

class Granary : public CityBuilding {
public:
    Granary();
    explicit Granary(int16_t accumulatedHammers);
    
    void setAccumulatedFood(int16_t food);
    int16_t accumulatedFood() const;

private: // CityBuilding
    virtual void processTurnGoods(City &city, Goods &turnGoods);
    virtual void processCityGrowth(City &city);

private:
    int16_t accumulatedFood_;
};

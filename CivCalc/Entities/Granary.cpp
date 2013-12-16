//
//  Granary.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 14.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Granary.h"
#include "City.h"
#include "Goods.h"
#include <algorithm>

Granary::Granary()
    : Granary(0)
{}

Granary::Granary(int16_t accumulatedHammers)
    : CityBuilding("Granary", false, 60, accumulatedHammers)
    , accumulatedFood_(0)
{}

void Granary::setAccumulatedFood(int16_t food) {
    accumulatedFood_ = food;
}

int16_t Granary::accumulatedFood() const {
    return accumulatedFood_;
}

void Granary::processTurnGoods(City &city, Goods &turnGoods) {
    const int16_t capacity = city.nextPopulationFood() / 2;
    if (accumulatedFood_ < capacity) {
        accumulatedFood_ = std::max<int16_t>(accumulatedFood_ + turnGoods.food, capacity);
    }
}

void Granary::processCityGrowth(City &city) {
    Goods cityGoods = city.accumulatedGoods();
    cityGoods.food += accumulatedFood_;
    city.setAccumulatedGoods(cityGoods);
}

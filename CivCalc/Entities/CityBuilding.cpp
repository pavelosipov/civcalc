//
//  CityBuilding.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 14.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "CityBuilding.h"
#include "City.h"

CityBuilding::CityBuilding(
    const std::string &name,
    bool eatsFood,
    int16_t requiredHammers,
    int16_t accumulatedHammers)
    : Building(name, eatsFood, requiredHammers, accumulatedHammers)
{}

void CityBuilding::consumeGoods(City &city, Goods &goods) {
    Building::consumeGoods(city, goods);
    if (isComleted()) {
        city.addCityBuilding(std::static_pointer_cast<CityBuilding>(shared_from_this()));
    }
}

void CityBuilding::processTurnGoods(City &city, Goods &turnGoods) {}
void CityBuilding::processCityGrowth(City &city) {}

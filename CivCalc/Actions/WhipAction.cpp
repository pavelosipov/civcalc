//
//  WhipAction.cpp
//  CivCalc
//
//  Created by Osipov on 02.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "WhipAction.h"
#include "City.h"

std::shared_ptr<WhipAction> WhipAction::create() {
    return std::make_shared<WhipAction>();
}

void WhipAction::processApply(City &city, Goods &turnGoods) {
    if (city.canWhip()) {
        city.whip();
    } else {
        city.turnLogger().addEvent("WHIP FAILED");
    }
}

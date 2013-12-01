//
//  Action.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 26.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Action.h"

Action::~Action()
{}

void Action::apply(City &city, Goods &turnGoods) {
    processApply(city, turnGoods);
}

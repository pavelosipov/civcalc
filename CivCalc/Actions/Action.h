//
//  Action.h
//  CivCalc
//
//  Created by Pavel Osipov on 26.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include <inttypes.h>

class City;
class Goods;

class Action {
public:
    virtual ~Action();

public:
    void apply(City &city, Goods &turnGoods);
    
private:
    virtual void processApply(City &city, Goods &turnGoods) = 0;
};

//
//  Goods.h
//  CivCalc
//
//  Created by Pavel Osipov on 24.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include <inttypes.h>
#include <ostream>

struct Goods {
    Goods();
    Goods(int8_t food, int8_t hammers, int8_t commerce);
    Goods(const Goods &other);
    Goods(Goods &&other);
    
    Goods &operator = (const Goods &other);
    Goods &operator -= (const Goods &other);
    Goods &operator += (const Goods &other);
    
    friend Goods operator + (const Goods &lhs, const Goods &rhs);
    friend Goods operator - (const Goods &lhs, const Goods &rhs);

    friend std::ostream& operator << (std::ostream &stream, const Goods &goods);
    
    int8_t food;
    int8_t hammers;
    int8_t commerce;
};

//
//  Goods.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 24.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Goods.h"
#include <iomanip>

Goods::Goods()
    : food(0)
    , hammers(0)
    , commerce(0)
{}

Goods::Goods(int16_t _food, int16_t _hammers, int16_t _commerce)
    : food(_food)
    , hammers(_hammers)
    , commerce(_commerce)
{}
    
Goods::Goods(const Goods &other)
    : food(other.food)
    , hammers(other.hammers)
    , commerce(other.commerce)
{}

Goods::Goods(Goods &&other)
    : food(other.food)
    , hammers(other.hammers)
    , commerce(other.commerce)
{}

Goods &Goods::operator = (const Goods &other) {
    food = other.food;
    hammers = other.hammers;
    commerce = other.commerce;
    return *this;
}

Goods &Goods::operator -= (const Goods &other) {
    food -= other.food;
    hammers -= other.hammers;
    commerce -= other.commerce;
    return *this;
}

Goods &Goods::operator += (const Goods &other) {
    food += other.food;
    hammers += other.hammers;
    commerce += other.commerce;
    return *this;
}

Goods operator + (const Goods &lhs, const Goods &rhs) {
    Goods result;
    result.food = lhs.food + rhs.food;
    result.hammers = lhs.hammers + rhs.hammers;
    result.commerce = lhs.commerce + rhs.commerce;
    return result;
}

Goods operator - (const Goods &lhs, const Goods &rhs) {
    Goods result;
    result.food = lhs.food - rhs.food;
    result.hammers = lhs.hammers - rhs.hammers;
    result.commerce = lhs.commerce - rhs.commerce;
    return result;
}

std::ostream& operator << (std::ostream &stream, const Goods &goods) {
    stream << std::setw(2) << static_cast<int>(goods.food) << "/"
           << std::setw(2) << static_cast<int>(goods.hammers) << "/"
           << std::setw(3) << static_cast<int>(goods.commerce);
    return stream;
}

bool Goods::isZero() const {
    return food == 0 && hammers == 0 && commerce == 0;
}

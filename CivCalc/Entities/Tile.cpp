//
//  Tile.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 30.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Tile.h"

Tile::Tile(const Goods &baseGoods)
    : baseGoods_(baseGoods)
{}

Tile::Tile(Tile &&other)
    : baseGoods_(std::move(other.baseGoods_))
{}

const Goods &Tile::goods() const {
    return baseGoods_;
}

std::ostream& operator << (std::ostream &stream, const Tile &tile) {
    stream << tile.baseGoods_;
    return stream;
}

std::shared_ptr<Tile> Tile::create(uint8_t food, uint8_t hammers, uint8_t commerce) {
    return std::make_shared<Tile>(Goods(food, hammers, commerce));
}

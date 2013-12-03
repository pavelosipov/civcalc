//
//  Tile.h
//  CivCalc
//
//  Created by Pavel Osipov on 30.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "Goods.h"
#include <memory>
#include <ostream>

class Tile {
public:
    explicit Tile(const Goods &baseGoods);
    Tile(Tile &&other);
    Tile(const Tile &other) = delete;
    Tile &operator = (const Tile &other) = delete;

    static std::shared_ptr<Tile> create(uint8_t food, uint8_t hammers, uint8_t commerce);

    const Goods &goods() const;
    void setGoods(const Goods &goods);
    
    friend std::ostream& operator << (std::ostream &stream, const Tile &tile);

private:
    Goods baseGoods_;
};

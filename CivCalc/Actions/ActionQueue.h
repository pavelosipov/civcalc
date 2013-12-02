//
//  ActionQueue.h
//  CivCalc
//
//  Created by Pavel Osipov on 01.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include <memory>
#include <queue>
#include <list>

class Action;
class City;
class Goods;

class ActionQueue {
    typedef std::list<std::shared_ptr<Action>> ActionList;
    struct Item {
        uint8_t turn;
        std::shared_ptr<Action> action;
        friend bool operator < (const Item &lhs, const Item &rhs) {
            return lhs.turn > rhs.turn;
        }
    };
    
public:
    void pushAction(uint8_t turn, std::shared_ptr<Action> action);
    void applyActions(uint8_t turn, City &city, Goods &turnGoods);
    
private:
    std::priority_queue<Item> actionQueue_;
};

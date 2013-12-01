//
//  EventQueue.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 01.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "ActionQueue.h"
#include "City.h"
#include "Action.h"

void ActionQueue::pushAction(uint8_t turn, std::shared_ptr<Action> action) {
    Item item;
    item.turn = turn;
    item.action = action;
    actionQueue_.push(item);
}

void ActionQueue::applyActions(uint8_t turn, City &city, Goods &turnGoods) {
    while (!actionQueue_.empty()) {
        if (actionQueue_.top().turn != turn) {
            break;
        }
        actionQueue_.top().action->apply(city, turnGoods);
        actionQueue_.pop();
    }
}

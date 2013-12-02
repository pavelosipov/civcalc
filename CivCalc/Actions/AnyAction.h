//
//  AnyAction.h
//  CivCalc
//
//  Created by Pavel Osipov on 01.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "Action.h"
#include <functional>
#include <memory>

class AnyAction: public Action {
    typedef std::function<void(City &city, Goods &turnGoods)> ProcessFunctor;
    
public:
    explicit AnyAction(const ProcessFunctor &functor);
    static std::shared_ptr<AnyAction> create(const ProcessFunctor &functor);

private:
    virtual void processApply(City &city, Goods &turnGoods);

private:
    ProcessFunctor processFunctor_;
};

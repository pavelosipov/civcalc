//
//  WhipAction.h
//  CivCalc
//
//  Created by Osipov on 02.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include "Action.h"
#include <memory>

class WhipAction: public Action {
public:
    static std::shared_ptr<WhipAction> create();
    
private:
    virtual void processApply(City &city, Goods &turnGoods);
};

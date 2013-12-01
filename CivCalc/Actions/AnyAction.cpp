//
//  AnyAction.cpp
//  CivCalc
//
//  Created by Pavel Osipov on 01.12.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "AnyAction.h"

AnyAction::AnyAction(const ProcessFunctor &functor)
    : processFunctor_(functor)
{}

void AnyAction::processApply(City &city, Goods &turnGoods) {
    processFunctor_(city, turnGoods);
}

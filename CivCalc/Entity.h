//
//  Entity.h
//  CivCalc
//
//  Created by Osipov on 26.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#pragma once

#include <stdint.h>

typedef uint16_t Id;

struct Entity {
    Id id;
    Entity(Id _id)
        : id(_id)
    {}
};

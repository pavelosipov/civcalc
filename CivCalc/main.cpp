//
//  main.cpp
//  CivCalc
//
//  Created by Osipov on 22.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Building.h"
#include "City.h"
#include "Tile.h"

#include "ActionQueue.h"
#include "AnyAction.h"
#include "WhipAction.h"

#include <iostream>

static void processAmsterdamBuildingQueue() {
    std::cout << "AMSTERDAM" << std::endl;
    City city;
    city.setPopulation(2);
    city.setTiles({
        Tile::create(2, 1, 11), // city
        Tile::create(5, 0, 3),  // fish
        Tile::create(4, 2, 1),  // cow
        Tile::create(1, 1, 0)   // mine
    });
    city.setAccumulatedGoods(Goods(14, 15, 0));
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::settler());
    city.pushBuilding(Building::worker());
    ActionQueue actionQueue;
    actionQueue.pushAction(8, AnyAction::create([](City &city, Goods &turnGoods) {
        city.setTopBuilding(Building::axeman());
    }));
    actionQueue.pushAction(10, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(1, 3, 0)); // mine improved
        city.swapBuildings(0, 1);
        city.swapBuildings(1, 2);
    }));
    actionQueue.pushAction(13, WhipAction::create());
    city.processBuildingQueue(0, actionQueue);
}

static void processUtrechtBuildingQueue() {
    std::cout << std::endl << "UTRECHT" << std::endl;
    City city;
    city.setTiles({
        Tile::create(2, 1, 2), // city
        Tile::create(5, 1, 1), // wheat
        Tile::create(1, 3, 1), // riverside mine
        Tile::create(3, 0, 0), // cows
        Tile::create(2, 0, 0), // riverside graasland
        Tile::create(2, 0, 0)  // riverside graasland
    });
    city.setPopulation(2);
    city.setAccumulatedGoods(Goods(4, 0, 0));
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::workBoat(10));
    city.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(11, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(4, 2, 0)); // cows improved
    }));
    city.processBuildingQueue(0, actionQueue);
}

static void processTheHagueBuildingQueue() {
    std::cout << std::endl << "THE HAGUE" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 1, 2), // city
        Tile::create(1, 5, 0), // copper
        Tile::create(4, 0, 3), // clam
        Tile::create(2, 0, 3)  // fish
    });
    city.pushBuilding(Building::galley());
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(1, AnyAction::create([](City &city, Goods &turnGoods) {
        city.swapTiles(1, 2);
    }));
    actionQueue.pushAction(3, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(7, AnyAction::create([](City &city, Goods &turnGoods) {
        city.swapBuildings(0, 1);
    }));
    actionQueue.pushAction(8, AnyAction::create([](City &city, Goods &turnGoods) {
        city.swapBuildings(0, 1);
    }));
    actionQueue.pushAction(14, WhipAction::create());
    city.processBuildingQueue(0, actionQueue);
}

int main(int argc, const char * argv[]) {
    processAmsterdamBuildingQueue();
    processUtrechtBuildingQueue();
    processTheHagueBuildingQueue();
    return 0;
}

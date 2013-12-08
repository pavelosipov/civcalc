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

static void processAmsterdamBuildingQueue(uint8_t startTurn) {
    std::cout << "AMSTERDAM" << std::endl;
    City city;
    city.setPopulation(2);
    city.setTiles({
        Tile::create(2, 1, 11), // city
        Tile::create(5, 0, 3),  // fish
        Tile::create(4, 2, 1),  // cow
        Tile::create(1, 3, 1),  // riverside mine
        Tile::create(2, 0, 1)   // riverside graasland
    });
    city.setAccumulatedGoods(Goods(14, 0, 0));
    city.pushBuilding(Building::worker(35));
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::settler());
    city.pushBuilding(Building::worker());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 5, AnyAction::create([](City &city, Goods &turnGoods) {
        city.swapBuildings(0, 1);
    }));
    actionQueue.pushAction(startTurn + 8, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 13, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(2, 0, 3)); // graasland improved
        city.turnLogger().addEvent("COTTAGE COMPLETED");
        city.swapTiles(3, 4);
    }));
//    actionQueue.pushAction(13, WhipAction::create());
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processUtrechtBuildingQueue(uint8_t startTurn) {
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
    actionQueue.pushAction(startTurn + 11, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(4, 2, 0)); // cows improved
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processTheHagueBuildingQueue(uint8_t startTurn) {
    std::cout << std::endl << "THE HAGUE" << std::endl;
    City city;
    city.setPopulation(1);
    city.setAccumulatedGoods(Goods(9, 0, 0));
    city.setTiles({
        Tile::create(2, 1, 2), // city
        Tile::create(4, 0, 3), // clam
        Tile::create(1, 5, 0), // copper
        Tile::create(2, 0, 3), // fish
        Tile::create(1, 1, 0)  // mine
    });
    city.pushBuilding(Building::galley(28));
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::barracks());
    city.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 8, WhipAction::create());
    actionQueue.pushAction(startTurn + 10, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(5, 0, 3)); // fish improved
        city.swapTiles(2, 3);
    }));
    actionQueue.pushAction(startTurn + 14, AnyAction::create([](City &city, Goods &turnGoods) {
        city.setTopBuilding(Building::settler());
    }));
    actionQueue.pushAction(startTurn + 27, WhipAction::create());
    city.processBuildingQueue(startTurn, actionQueue);
}

int main(int argc, const char * argv[]) {
    const uint8_t startTurn = 45;
    processAmsterdamBuildingQueue(startTurn);
//    processUtrechtBuildingQueue(startTurn);
    processTheHagueBuildingQueue(startTurn);
    return 0;
}

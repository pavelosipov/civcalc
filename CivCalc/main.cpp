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

static void processRomeBuildingQueue(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(5);
    city.setAccumulatedGoods(Goods(20, 0, 0));
    city.setTiles({
        Tile::create(2, 1, 9), // city
        Tile::create(4, 0, 3), // clam
        Tile::create(3, 3, 1), // cows
        Tile::create(1, 3, 1), // riverside hill
        Tile::create(2, 0, 3), // cottage
        Tile::create(2, 0, 3)  // cottage
    });
//    city.pushBuilding(Building::spearman(12));
    city.pushBuilding(Building::axeman(6));
    ActionQueue actionQueue;
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processAntiumBuildingQueue(uint8_t startTurn) {
    std::cout << "ANTIUM" << std::endl;
    City city;
    city.setPopulation(3);
    city.setAccumulatedGoods(Goods(3, 6, 0));
    city.setTiles({
        Tile::create(2, 1, 2), // city
        Tile::create(6, 0, 0), // pigs
        Tile::create(5, 1, 1), // wheat
        Tile::create(2, 0, 4), // hamlet
    });
    city.pushBuilding(Building::granary(45));
    ActionQueue actionQueue;
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processCumaeBuildingQueue(uint8_t startTurn) {
    std::cout << "CUMAE" << std::endl;
    City city;
    city.setPopulation(4);
    city.setAccumulatedGoods(Goods(0, 0, 0));
    city.setTiles({
        Tile::create(2, 1, 2), // city
        Tile::create(6, 0, 1), // corn
        Tile::create(1, 5, 1), // copper
        Tile::create(2, 0, 3), // cottage
        Tile::create(1, 3, 3), // riverside mine
    });
    city.pushBuilding(Building::spearman(26));
    city.pushBuilding(Building::granary(16));
    ActionQueue actionQueue;
    city.processBuildingQueue(startTurn, actionQueue);
}

int main(int argc, const char * argv[]) {
    const uint8_t startTurn = 74;
//    processMiddleburgBuildingQueue(startTurn);
    processRomeBuildingQueue(startTurn);
    processAntiumBuildingQueue(startTurn);
//    processNijmegenBuildingQueue(startTurn);
//    processAmsterdamBuildingQueue(startTurn);
//    processUtrechtBuildingQueue(startTurn);
//    processTheHagueBuildingQueue(startTurn);
//    processRotterdamBuildingQueue(startTurn);
    return 0;
}

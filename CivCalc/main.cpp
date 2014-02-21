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
    city.pushBuilding(Building::spearman(12));
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
        Tile::create(2, 0, 4), // hamlet
        Tile::create(2, 1, 0), // forest
        Tile::create(0, 0, 3), // scientist
        Tile::create(0, 0, 3)  // scientist
    });
    city.pushBuilding(Building::granary(45));
    city.pushBuilding(Building::library());
    city.pushBuilding(Building::settler());
    city.pushBuilding(Building::barracks());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 3, AnyAction::create([](City &city, Goods &turnGoods){
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 7, AnyAction::create([](City &city, Goods &turnGoods){
        city.tileAt(5)->setGoods(Goods(2, 0, 3));
        city.turnLogger().addEvent("COTTAGE");
    }));
    actionQueue.pushAction(startTurn + 8, AnyAction::create([](City &city, Goods &turnGoods){
        city.whip();
    }));
    actionQueue.pushAction(startTurn + 9, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("+2 SCIENTISTS");
        city.swapTiles(3, 6);
        city.swapTiles(4, 7);
    }));
    actionQueue.pushAction(startTurn + 14, AnyAction::create([](City &city, Goods &turnGoods){
        city.whip();
    }));
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
        Tile::create(1, 3, 1), // riverside mine
        Tile::create(2, 0, 0), // graasland
        Tile::create(2, 0, 3), // crab
    });
    city.pushBuilding(Building::spearman(26));
    city.pushBuilding(Building::granary(16));
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::barracks());
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::spearman());
    city.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 2, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("SWAP: COPPER <-> GRAASLAND");
        city.swapTiles(2, 5);
    }));
    actionQueue.pushAction(startTurn + 3, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("SWAP: GRAASLAND <-> COPPER");
        city.swapTiles(2, 5);
        city.whip();
    }));
    actionQueue.pushAction(startTurn + 6, AnyAction::create([](City &city, Goods &turnGoods){
        city.tileAt(6)->setGoods(Goods(4, 0, 3));
        city.swapTiles(3, 6);
        city.swapTiles(5, 6);
    }));
    actionQueue.pushAction(startTurn + 17, AnyAction::create([](City &city, Goods &turnGoods){
        city.setTopBuilding(Building::settler());
    }));
    actionQueue.pushAction(startTurn + 18, AnyAction::create([](City &city, Goods &turnGoods){
        city.whip();
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

int main(int argc, const char * argv[]) {
    const uint8_t startTurn = 74;
    processRomeBuildingQueue(startTurn);
    processAntiumBuildingQueue(startTurn);
    processCumaeBuildingQueue(startTurn);
    return 0;
}

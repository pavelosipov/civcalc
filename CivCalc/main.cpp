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

static void processRomeBuildingQueue1(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 2, 9), // city
        Tile::create(0, 3, 0), // plain hill forest
        Tile::create(5, 0, 2), // fish
        Tile::create(3, 0, 0), // pigs
        Tile::create(1, 1, 0), // hills
        Tile::create(2, 0, 2), // crab
    });
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::settler());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 7, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("FOREST -> FISH");
        city.swapTiles(1, 2);
    }));
    actionQueue.pushAction(startTurn + 18, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("PIGS PASTURE");
        city.tileAt(3)->setGoods(Goods(6, 0, 0));
        city.swapTiles(1, 3);
        city.swapTiles(2, 3);
    }));
    actionQueue.pushAction(startTurn + 23, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("MINE");
        city.tileAt(4)->setGoods(Goods(1, 3, 0));
        city.swapTiles(3, 4);
    }));
    actionQueue.pushAction(startTurn + 26, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("CRAB NETS");
        city.tileAt(5)->setGoods(Goods(4, 0, 2));
        city.swapTiles(4, 5);
    }));
    actionQueue.pushAction(startTurn + 27, AnyAction::create([](City &city, Goods &turnGoods){
        city.chop();
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processRomeBuildingQueue2(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 2, 9), // city
        Tile::create(0, 3, 0), // plain hill forest
        Tile::create(5, 0, 2), // fish
        Tile::create(3, 0, 0), // pigs
        Tile::create(1, 1, 0), // hills
        Tile::create(2, 0, 2), // crab
    });
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::settler());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 7, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("FOREST -> FISH");
        city.swapTiles(1, 2);
    }));
    actionQueue.pushAction(startTurn + 19, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("MINE");
        city.tileAt(4)->setGoods(Goods(1, 3, 0));
        city.swapTiles(2, 4);
    }));
    actionQueue.pushAction(startTurn + 23, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("PIGS PASTURE");
        city.tileAt(3)->setGoods(Goods(6, 0, 0));
        city.swapTiles(2, 3);
    }));
    actionQueue.pushAction(startTurn + 24, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("CRAB NETS");
        city.tileAt(5)->setGoods(Goods(4, 0, 2));
        city.swapTiles(4, 5);
    }));
    actionQueue.pushAction(startTurn + 28, AnyAction::create([](City &city, Goods &turnGoods){
        city.chop();
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processRomeBuildingQueue3(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 2, 9), // city
        Tile::create(0, 3, 0), // plain hill forest
        Tile::create(3, 0, 0), // pigs
        Tile::create(2, 0, 2), // crab
        Tile::create(5, 0, 2), // fish
        Tile::create(1, 1, 0), // hills
    });
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::settler());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 16, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("MINE");
        city.tileAt(5)->setGoods(Goods(1, 3, 0));
        city.swapTiles(5, 1);
    }));
    actionQueue.pushAction(startTurn + 19, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("FISH NETS");
        city.tileAt(4)->setGoods(Goods(5, 0, 2));
        city.swapTiles(4, 1);
    }));
    actionQueue.pushAction(startTurn + 20, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("PIGS PASTURE");
        city.tileAt(2)->setGoods(Goods(6, 0, 0));
        city.swapTiles(2, 1);
    }));
    actionQueue.pushAction(startTurn + 24, AnyAction::create([](City &city, Goods &turnGoods){
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 25, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("CRAB NETS");
        city.tileAt(3)->setGoods(Goods(4, 0, 2));
    }));
    actionQueue.pushAction(startTurn + 28, AnyAction::create([](City &city, Goods &turnGoods){
        city.chop();
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processRomeBuildingQueueIndustrious(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 2, 9), // city
        Tile::create(0, 3, 0), // plain hill forest
        Tile::create(5, 0, 2), // fish
        Tile::create(2, 0, 2), // crab
        Tile::create(3, 0, 0), // pigs
        Tile::create(1, 1, 0), // hills
    });
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::stonehenge());
    city.pushBuilding(Building::warrior());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 5, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("FOREST -> FISH");
        city.swapTiles(1, 2);
    }));
    actionQueue.pushAction(startTurn + 16, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("MINE");
        city.tileAt(5)->setGoods(Goods(1, 3, 0));
        city.swapTiles(2, 5);
    }));
    actionQueue.pushAction(startTurn + 19, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("CRAB NETS");
        city.tileAt(3)->setGoods(Goods(4, 0, 2));
        city.swapTiles(3, 2);
    }));
    actionQueue.pushAction(startTurn + 20, AnyAction::create([](City &city, Goods &turnGoods){
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 24, AnyAction::create([](City &city, Goods &turnGoods){
        city.turnLogger().addEvent("MINE");
        city.tileAt(5)->setGoods(Goods(0, 4, 0));
        city.swapTiles(5, 4);
//        city.chop();
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

int main(int argc, const char * argv[]) {
    const uint8_t startTurn = 0;
    processRomeBuildingQueueIndustrious(startTurn);
    return 0;
}

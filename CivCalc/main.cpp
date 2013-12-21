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
    city.setPopulation(3);
    city.setTiles({
        Tile::create(2, 1, 11), // city
        Tile::create(5, 0, 3),  // fish
        Tile::create(4, 2, 1),  // cow
        Tile::create(2, 0, 3),  // riverside graasland cottage
        Tile::create(2, 0, 3),  // riverside graasland cottage
        Tile::create(1, 3, 1)   // riverside mine
    });
    city.setAccumulatedGoods(Goods(4, 0, 0));
    city.pushBuilding(Building::settler(84));
    city.pushBuilding(Building::workBoat(11));
    city.pushBuilding(Building::granary());
    city.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 10, WhipAction::create());
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processUtrechtBuildingQueue(uint8_t startTurn) {
    std::cout << std::endl << "UTRECHT" << std::endl;
    City city;
    city.setTiles({
        Tile::create(2, 1, 2), // city
        Tile::create(4, 2, 0), // cows
        Tile::create(5, 1, 1), // wheat
        Tile::create(2, 0, 3), // improved cottage
        Tile::create(2, 0, 0), // cottage
        Tile::create(1, 3, 1), // riverside mine
    });
    city.setPopulation(2);
    city.setAccumulatedGoods(Goods(15, 0, 0));
    city.pushBuilding(Building::warrior(12));
    city.pushBuilding(Building::granary(4));
    city.pushBuilding(Building::axeman());
    city.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 3, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(2, 0, 3));
        city.turnLogger().addEvent("COTTAGE IMPROVED");
    }));
    actionQueue.pushAction(startTurn + 5, AnyAction::create([](City &city, Goods &turnGoods) {
        city.setTopBuilding(Building::settler());
    }));
    actionQueue.pushAction(startTurn + 11, WhipAction::create());
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processTheHagueBuildingQueue(uint8_t startTurn) {
    std::cout << std::endl << "THE HAGUE" << std::endl;
    City city;
    city.setPopulation(1);
    city.setAccumulatedGoods(Goods(19, 0, 0));
    city.setTiles({
        Tile::create(2, 1, 2), // city
        Tile::create(4, 0, 3), // clam
        Tile::create(5, 0, 3), // fish
        Tile::create(1, 5, 0), // copper
        Tile::create(1, 1, 0)  // mine
    });
    city.pushBuilding(Building::workBoat());
    city.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 1, WhipAction::create());
    actionQueue.pushAction(startTurn + 10, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(5, 0, 3)); // fish improved
        city.swapTiles(2, 3);
    }));
    actionQueue.pushAction(startTurn + 14, AnyAction::create([](City &city, Goods &turnGoods) {
        city.setTopBuilding(Building::settler());
    }));
    actionQueue.pushAction(startTurn + 11, WhipAction::create());
    actionQueue.pushAction(startTurn + 19, WhipAction::create());
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processRotterdamBuildingQueue(uint8_t startTurn) {
    std::cout << std::endl << "ROTTERDAM" << std::endl;
    City city;
    city.setPopulation(2);
    city.setAccumulatedGoods(Goods(22, 0, 0));
    city.setTiles({
        Tile::create(2, 2, 3), // city
        Tile::create(4, 0, 3), // clam
        Tile::create(2, 3, 1), // horses
        Tile::create(1, 0, 3), // coast
        Tile::create(1, 0, 3), // coast
        Tile::create(1, 0, 3), // coast
        Tile::create(1, 0, 3), // coast
        Tile::create(1, 0, 3)  // coast
    });
    city.pushBuilding(Building::granary(33));
    city.pushBuilding(Building::lighthouse(4));
    city.pushBuilding(Building::archer());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 2, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(1, 3, 0));
    }));
    actionQueue.pushAction(startTurn + 5, WhipAction::create());
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processNijmegenBuildingQueue(uint8_t startTurn) {
    std::cout << "NIJMEGEN" << std::endl;
    City city;
    city.setPopulation(1);
    city.setAccumulatedGoods(Goods(10, 0, 0));
    city.setTiles({
        Tile::create(2, 1, 3), // city
        Tile::create(2, 0, 3), // lake
        Tile::create(2, 0, 3), // lake
        Tile::create(2, 0, 3)  // lake
    });
    city.pushBuilding(Building::library());
    city.pushBuilding(Building::lighthouse(5));
    city.pushBuilding(Building::granary());
    city.pushBuilding(Building::archer());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 2, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 4, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 5, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 6, WhipAction::create());
    actionQueue.pushAction(startTurn + 16, WhipAction::create());
    actionQueue.pushAction(startTurn + 7, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(1)->setGoods(Goods(3, 0, 3));
        city.tileAt(2)->setGoods(Goods(3, 0, 3));
        city.tileAt(3)->setGoods(Goods(3, 0, 3));
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processRomeBuildingQueue(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 1, 9), // city
        Tile::create(4, 0, 3), // plains hill with forest
        Tile::create(2, 1, 1), // wheat
        Tile::create(2, 1, 1), // cows
        Tile::create(1, 2, 0)  // hill
    });
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::settler());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::barracks());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn +  2, AnyAction::create([](City &city, Goods &turnGoods) { city.turnLogger().addEvent("AGRICULTURE"); }));
    actionQueue.pushAction(startTurn + 17, AnyAction::create([](City &city, Goods &turnGoods) { city.turnLogger().addEvent("BRONZE WORKING (15 TURNS)"); }));
    actionQueue.pushAction(startTurn + 30, AnyAction::create([](City &city, Goods &turnGoods) { city.turnLogger().addEvent("ANIMAL HUSBANDRY (12 TURNS)"); }));
    actionQueue.pushAction(startTurn + 17, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(2)->setGoods(Goods(4, 1, 1));
        city.turnLogger().addEvent("WHEAT FARM");
    }));
    actionQueue.pushAction(startTurn + 21, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 25, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(startTurn + 27, AnyAction::create([](City &city, Goods &turnGoods) {
        turnGoods = Goods(-6, -3, -14);
        city.turnLogger().addEvent("REVOLUTION");
    }));
    actionQueue.pushAction(startTurn + 29, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
        city.whip();
    }));
    actionQueue.pushAction(startTurn + 29, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(1, 3, 1));
        city.turnLogger().addEvent("MINE");
    }));
    actionQueue.pushAction(startTurn + 33, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(3, 3, 1));
        city.turnLogger().addEvent("PASTURE");
    }));
    actionQueue.pushAction(startTurn + 38, AnyAction::create([](City &city, Goods &turnGoods) {
        city.setTopBuilding(Building::settler());
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

/*
static void processRomeBuildingQueue(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 1, 9), // city
        Tile::create(4, 0, 3), // clam
        Tile::create(2, 1, 0), // wheat
        Tile::create(2, 1, 1), // cows
        Tile::create(1, 1, 0)  // hill
    });
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::settler());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::worker());
    ActionQueue actionQueue;
    actionQueue.pushAction(startTurn + 2, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("AGRICULTURE");
    }));
    actionQueue.pushAction(startTurn + 17, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(2)->setGoods(Goods(4, 1, 1));
        city.swapTiles(1, 2);
        city.turnLogger().addEvent("FARM");
    }));
    actionQueue.pushAction(startTurn + 14, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("ANIMAL HUSBANDRY (12)");
    }));
    actionQueue.pushAction(startTurn + 29, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("BRONZE WORKING (15)");
    }));
    actionQueue.pushAction(31, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(3, 3, 1));
        city.turnLogger().addEvent("PASTURE, NOTHING TODO FOR WORKER UNTIL BW");
    }));
    actionQueue.pushAction(39, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(44, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(1, 3, 1));
        city.turnLogger().addEvent("MINE");
    }));
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processRomeBuildingQueue(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 1, 9), // city
        Tile::create(4, 0, 3), // clam
        Tile::create(2, 1, 0), // wheat
        Tile::create(2, 1, 1), // cows
        Tile::create(1, 1, 0)  // hill
    });
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::settler());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::worker());
    ActionQueue actionQueue;
    actionQueue.pushAction(25, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(2)->setGoods(Goods(4, 1, 1));
        city.swapTiles(1, 2);
        city.turnLogger().addEvent("FARM");
    }));
    actionQueue.pushAction(10, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("AC");
    }));
    actionQueue.pushAction(25, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("BW(15)");
    }));
    actionQueue.pushAction(37, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("AH(12)");
    }));
    actionQueue.pushAction(29, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(33, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(1, 3, 1));
        city.turnLogger().addEvent("MINE");
        city.swapTiles(3, 4);
    }));
    actionQueue.pushAction(37, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(41, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(3, 3, 1));
        city.turnLogger().addEvent("PASTURE");
        city.swapTiles(3, 4);
    }));
    
    city.processBuildingQueue(startTurn, actionQueue);
}

static void processRomeBuildingQueue(uint8_t startTurn) {
    std::cout << "ROME" << std::endl;
    City city;
    city.setPopulation(1);
    city.setTiles({
        Tile::create(2, 1, 9), // city
        Tile::create(4, 0, 3), // clam
        Tile::create(2, 1, 0), // wheat
        Tile::create(2, 1, 1), // cows
        Tile::create(1, 1, 0)  // hill
    });
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::warrior());
    city.pushBuilding(Building::worker());
    city.pushBuilding(Building::settler());
    city.pushBuilding(Building::warrior());
    ActionQueue actionQueue;
    actionQueue.pushAction(25, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(2)->setGoods(Goods(4, 1, 1));
        city.swapTiles(1, 2);
        city.turnLogger().addEvent("FARM");
    }));
    actionQueue.pushAction(10, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("AC");
    }));
    actionQueue.pushAction(25, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("BW(15)");
    }));
    actionQueue.pushAction(37, AnyAction::create([](City &city, Goods &turnGoods) {
        city.turnLogger().addEvent("AH(12)");
    }));
    actionQueue.pushAction(29, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(33, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(1, 3, 1));
        city.swapTiles(3, 4);
        city.turnLogger().addEvent("MINE");
    }));
    actionQueue.pushAction(37, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(38, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(42, AnyAction::create([](City &city, Goods &turnGoods) {
        city.chop();
    }));
    actionQueue.pushAction(41, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(4)->setGoods(Goods(3, 3, 1));
        city.turnLogger().addEvent("PASTURE");
        city.swapTiles(3, 4);
    }));
    
    city.processBuildingQueue(startTurn, actionQueue);
}
*/
int main(int argc, const char * argv[]) {
    const uint8_t startTurn = 8;
    processRomeBuildingQueue(startTurn);
//    processNijmegenBuildingQueue(startTurn);
//    processAmsterdamBuildingQueue(startTurn);
//    processUtrechtBuildingQueue(startTurn);
//    processTheHagueBuildingQueue(startTurn);
//    processRotterdamBuildingQueue(startTurn);
    return 0;
}

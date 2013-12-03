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

int main(int argc, const char * argv[]) {
    City utrechtCity;
    utrechtCity.setTiles({
        Tile::create(2, 1, 1), // city
        Tile::create(5, 1, 1), // wheat
        Tile::create(1, 3, 1), // riverside mine
        Tile::create(3, 0, 0)  // cows
    });
    //utrechtCity.setAccumulatedGoods(Goods(6, 0, 0));
    utrechtCity.pushBuilding(Building::workBoat());
    utrechtCity.pushBuilding(Building::axeman());
    ActionQueue actionQueue;
    actionQueue.pushAction(5, AnyAction::create([](City &city, Goods &turnGoods) {
        city.setTopBuilding(Building::worker());
    }));
    actionQueue.pushAction(14, AnyAction::create([](City &city, Goods &turnGoods) {
        city.tileAt(3)->setGoods(Goods(4, 2, 0));
        city.swapTiles(2, 3);
    }));
    actionQueue.pushAction(9, WhipAction::create());
    utrechtCity.processBuildingQueue(0, actionQueue);

//    City amsterdamCity;
//    amsterdamCity.setPopulation(2);
//    amsterdamCity.setTiles({
//        Goods(2, 1, 9), // city
//        Goods(5, 0, 3), // fish
//        Goods(4, 2, 1), // cow
//        Goods(1, 3, 0)  // mine
//    });
//    amsterdamCity.setAccumulatedGoods(Goods(0, 15, 0));
//    UserEvents events;
//    events.whipTurn = 15;
//    events.whipCount = 1;
//    events.revolutionTurn = -20;
//    events.chopTurn = 14;
//    amsterdamCity.enqueueBuilding(Building("WORKER   ", true,  60));
//    amsterdamCity.enqueueBuilding(Building("WARRIOR  ", false, 15));
//    amsterdamCity.enqueueBuilding(Building("SETTLER  ", true,  100));
//    amsterdamCity.enqueueBuilding(Building("WORKER   ", true,  60));
//    amsterdamCity.processBuildingQueue(events);

//    City nonameCity;
//    nonameCity.setPopulation(1);
//    nonameCity.setTiles({
//        Goods(2, 1, 1), // city
//        Goods(4, 0, 3), // clam
//        Goods(1, 5, 0), // copper
//        Goods(5, 0, 3)  // fish
//    });
//    nonameCity.setAccumulatedGoods(Goods(00, 00, 00));
//    UserEvents events;
//    events.whipTurn = 11;
//    events.whipCount = 1;
//    events.revolutionTurn = -20;
//    events.chopTurn = 0;
//    nonameCity.enqueueBuilding(Building("GALLEY   ", false,  50));
//    nonameCity.enqueueBuilding(Building("WORK BOAT", false,  30));
//    nonameCity.processBuildingQueue(events);

    return 0;
}

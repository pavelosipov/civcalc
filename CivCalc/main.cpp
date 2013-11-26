//
//  main.cpp
//  CivCalc
//
//  Created by Osipov on 22.11.13.
//  Copyright (c) 2013 Pavel Osipov. All rights reserved.
//

#include "Building.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>
#include <iomanip>
#include <queue>
#include <assert.h>

struct UserEvents {
    uint8_t whipTurn;
    uint8_t whipCount;
    uint8_t revolutionTurn;
    uint8_t chopTurn;
    bool isValid() const {
        return whipTurn != revolutionTurn;
    }
};

class City {
    static const uint8_t MaxWorkingPopulationCount = 5;
public:
    City(): population_(1)
    {}
    
    uint8_t population() const                   { return population_; }
    void setPopulation(uint8_t population)       { population_ = population; }
    
    const Goods &accumulatedGoods() const        { return accumulatedGoods_; }
    void setAccumulatedGoods(const Goods &goods) { accumulatedGoods_ = goods; }
    
    void enqueueBuilding(const Building &building) {
        buildingQueue_.push(building);
    }
    
    void addTile(Goods tile) {
        tiles_.emplace_back(tile);
    }
    
    void setTiles(std::vector<Goods> &&tiles) {
        tiles_.swap(tiles);
    }
    
    void processBuildingQueue(const UserEvents &events) {
        assert(events.isValid());
        uint8_t turn = 0;
        while (!buildingQueue_.empty()) {
            Goods turnGoods(0, accumulatedGoods_.hammers, 0);
            accumulatedGoods_.hammers = 0;
            if (turn == events.whipTurn) {
                assert(events.whipCount < population_);
                turnGoods.hammers += 30 * events.whipCount;
                population_ -= events.whipCount;
            }
            const uint8_t workingTilesCount = population_ > MaxWorkingPopulationCount ? MaxWorkingPopulationCount : population_ + 1;
            if (turn != events.revolutionTurn) {
                turnGoods += std::accumulate(tiles_.begin(),
                                             tiles_.begin() + workingTilesCount,
                                             Goods(),
                                             [](const Goods &lhs, const Goods &rhs) -> Goods {
                                                 return lhs + rhs;
                                             });
                turnGoods.food -= 2 * population_;
            }
            if (turn == events.chopTurn) {
                if (turn != events.revolutionTurn) {
                    turnGoods.hammers += 20;
                } else {
                    accumulatedGoods_.hammers += 20;
                }
            }
            Building *currentBuilding = &buildingQueue_.front();
            std::cout << std::setfill('0');
            std::cout << "T" << std::setw(2) << static_cast<int>(turn) << ": " << "\t"
                      << *this << "\t"
                      << turnGoods
                      << "\t" << *currentBuilding
                      << ((currentBuilding->isComleted()) ? "\tCOMPLETED " : "")
                      << ((turn == events.whipTurn)       ? "\tWHIP      " : "")
                      << ((turn == events.revolutionTurn) ? "\tREVOLUTION" : "")
                      << ((turn == events.chopTurn)       ? "\tCHOP      " : "")
                      << std::endl;
            if (currentBuilding->isComleted()) {
                buildingQueue_.pop();
                if (buildingQueue_.empty()) {
                    return;
                } else {
                    currentBuilding = &buildingQueue_.front();
                }
            }
            currentBuilding->applyGoods(turnGoods);
            accumulatedGoods_ += turnGoods;
            const uint8_t requiredFood = 20 + 2 * population_;
            if (accumulatedGoods_.food >= requiredFood) {
                accumulatedGoods_.food -= requiredFood;
                ++population_;
            }
            ++turn;
        }
    }
    
    friend std::ostream& operator << (std::ostream &stream, const City &city) {
        stream << std::setw(2) << static_cast<int>(city.population_) << "\t" << city.accumulatedGoods_;
        return stream;
    }
    
private:
    uint8_t population_;
    Goods accumulatedGoods_;
    std::vector<Goods> tiles_;
    std::queue<Building> buildingQueue_;
};

//struct Whip : Event {
//    uint8_t populationCost;
//    uint8_t apply(City &city, Goods &cityTurnGoods) const {
//        assert(populationCost < city.population());
//        cityTurnGoods.hammerCount += 30 * populationCost;
//        return 0;
//    }
//};
//
//struct Revolution : Event {
//    uint8_t duration;
//    uint8_t apply(City &city, Goods &cityTurnGoods) const {
//        cityTurnGoods = {0, 0, 0};
//        return --duration;
//    }
//};

int main(int argc, const char * argv[]) {
    City amsterdamCity;
    amsterdamCity.setPopulation(4);
    amsterdamCity.setTiles({
        Goods(2, 1, 9), // city
        Goods(5, 0, 3), // fish
        Goods(4, 2, 1), // cow
        Goods(5, 1, 1), // wheat
        Goods(1, 3, 1)  // riverside mine
    });
    amsterdamCity.setAccumulatedGoods(Goods(0, 16, 0));
    UserEvents events;
    events.whipTurn = 2;
    events.whipCount = 2;
    events.revolutionTurn = -2;
    events.chopTurn = 0;
    Building workBoat("WORK BOAT", 30, false);
    workBoat.setAccumulatedHammers(6);
    amsterdamCity.enqueueBuilding(Building("SETTLER  ", 100, true));
    amsterdamCity.enqueueBuilding(workBoat);
    amsterdamCity.enqueueBuilding(Building("WARRIOR  ", 15,  false));
    amsterdamCity.enqueueBuilding(Building("WORKER   ", 60,  true));
    amsterdamCity.enqueueBuilding(Building("WARRIOR  ", 15,  false));
    amsterdamCity.processBuildingQueue(events);
    
//    City amsterdamCity;
//    amsterdamCity.setPopulation(4);
//    amsterdamCity.setTiles({
//        Goods(2, 1, 9), // city
//        Goods(5, 0, 3), // fish
//        Goods(4, 2, 1), // cow
//        Goods(5, 1, 1), // wheat
//        Goods(1, 3, 1)  // riverside mine
//    });
//    amsterdamCity.setAccumulatedGoods(Goods(0, 16, 0));
//    UserEvents events;
//    events.whipTurn = 2;
//    events.whipCount = 2;
//    events.revolutionTurn = -2;
//    events.chopTurn = 0;
//    Building workBoat("WORK BOAT", 30, false);
//    workBoat.setAccumulatedHammers(6);
//    amsterdamCity.enqueueBuilding(Building("SETTLER  ", 100, true));
//    amsterdamCity.enqueueBuilding(workBoat);
//    amsterdamCity.enqueueBuilding(Building("WARRIOR  ", 15,  false));
//    amsterdamCity.enqueueBuilding(Building("WORKER   ", 60,  true));
//    amsterdamCity.enqueueBuilding(Building("WARRIOR  ", 15,  false));
//    amsterdamCity.processBuildingQueue(events);
    
    return 0;
}

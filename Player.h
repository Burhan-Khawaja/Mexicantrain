#pragma once
#include "Train.h"
#include "Hand.h"
#include <iostream>

class Player {
public:
    virtual void addTileToHand(Tile tileToAdd) = 0;
    virtual void addTileToTrain(Tile tileToAdd) = 0;
    void printHelloWorld() { std::cout << "Hello Worl"; }
    void printTrain();
    void printHand();
    void removeTileFromHand(int value1, int value2);
    bool getTrainMarker();

protected:    
    Train playerTrain;
    Hand playerHand;
private:

};
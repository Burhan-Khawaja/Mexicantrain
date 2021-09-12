#pragma once
#include "Train.h"
#include "Hand.h"
#include <iostream>

class Player {
public:
    virtual void addTileToHand(Tile tileToAdd) = 0;
    virtual void addTileToTrain(Tile tileToAdd) = 0;    
    virtual bool tileFitsOnTrain(Tile tileToCheck, int engineInt) = 0;

    void printHelloWorld() { std::cout << "Hello Worl"; }
    void printTrain();
    void printHand();
    void removeTileFromHand(int value1, int value2);
    bool getTrainMarker();
    bool getOrphanDouble();
    //funciton to set orphan double to test code
    void setOrphanDouble() { playerTrain.setOrphanDouble(); };
    void resetOrphanDouble() { playerTrain.resetOrphanDouble(); }
    bool isTrainEmpty();
protected:    
    Train playerTrain;
    Hand playerHand;
private:

};
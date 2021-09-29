#pragma once
#include <iostream>
#include <deque>
#include "Tile.h"

class Train {
public:

    Train();

    bool const getMarker();

    bool const getOrphanDouble();

    int const getTrainEndNumber();

    bool isEmpty();

    std::deque<Tile> getTrainDeque();

    void setTrainEndNumber(int newEndNumber);

    void setMarker();

    void setOrphanDouble();

    void addTileFront(Tile tileToAdd);

    void addTileBack(Tile tileToAdd);

    void resetTrain();

    void clearMarker();

    void printTrain();

    void resetOrphanDouble();

    void clearTrain();

protected:
private:
    //holds all the tiles of the train
    std::deque<Tile> trainDeque;
    
    bool marker;
    bool orphanDouble;
    //The train end number is the trains last value that new tiles must match to be added to the train.
    int trainEndNumber;

};
#pragma once
#include <iostream>
#include <deque>
#include "Tile.h"

class Train {
public:
    void addTileFront(Tile tileToAdd);
    void addTileBack(Tile tileToAdd);
    Tile getLastTile();
    Tile getFirstTile();
    void getLastNumber();
    void resetTrain();
    void clearMarker();
    void setMarker();
    void printTrain();
protected:
private:
    bool marker;
    std::deque<Tile> trainDeque;

};
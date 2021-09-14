#pragma once
#include "Player.h"
#include <iostream>

class Human : public Player {
public:
    Human();
    void addTileToHand(Tile tileToAdd);
    void addTileToTrain(Tile tileToAdd);
    //bool tileFitsOnTrain(Tile tileToCheck, int engineInt);

protected:
private:

};
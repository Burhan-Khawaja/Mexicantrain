#pragma once
#include "Player.h"
#include <iostream>
class Computer : public Player {
public:    
    Computer() {
        //playerHand.addTile(Tile(1, 1));
        //playerTrain.addTileFront(Tile(1, 1));
    }
    void addTileToHand(Tile tileToAdd) {
        playerHand.addTile(tileToAdd);
    }
    void addTileToTrain(Tile tileToAdd) {
        playerTrain.addTileBack(tileToAdd);
    }

protected:
private:

};
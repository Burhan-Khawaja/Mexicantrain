#pragma once
#include "Player.h"
#include <iostream>
class Computer : public Player{
public:    
    Computer() {
        playerHand.addTile(Tile(1, 1));
        playerTrain.addTileFront(Tile(1, 1));
    }
    void addTile(Tile tileToAdd) {
        std::cout << "Testing, computer add tile function called";
    }

protected:
private:

};
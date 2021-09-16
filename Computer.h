#pragma once
#include "Player.h"

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
    Tile play(bool humanTrainPlayable, bool computerTrainPlayable, bool mexicanTrainPlayable) {
        return Tile(-1, -1);
    }
    virtual void play2Test(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain) {

    }
protected:
private:

};
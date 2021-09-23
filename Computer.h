#pragma once
#include "Player.h"
#include <vector>
class Computer : public Player {
public:    
    Computer();
    void addTileToHand(Tile tileToAdd);
    void addTileToTrain(Tile tileToAdd);
    int play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard);
protected:
private:

};
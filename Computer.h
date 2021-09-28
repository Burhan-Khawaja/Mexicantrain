#pragma once
#include "Player.h"
#include <vector>
class Computer : public Player {
public:    
    Computer();
    void addTileToTrain(Tile tileToAdd);
    int play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber,int engine);
    int checkGameWon(Player * humanPlayer);
protected:
private:

};
#pragma once
#include "Player.h"
#include "Computer.h"
#include <iostream>

class Human : public Player {
public:
    Human();
    void addTileToTrain(Tile tileToAdd);
    void playedDoubleTile(char userInput, Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard);
    int play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber,int engine);
protected:
private:

};
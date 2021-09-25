#pragma once
#include "Player.h"
#include "Computer.h"
#include <iostream>

class Human : public Player {
public:
    Human();
    void addTileToHand(Tile tileToAdd);
    void addTileToTrain(Tile tileToAdd);
    //bool tileFitsOnTrain(Tile tileToCheck, int engineInt);
    void playedDoubleTile(char userInput, Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard);
    int play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber,int engine);
protected:
private:

};
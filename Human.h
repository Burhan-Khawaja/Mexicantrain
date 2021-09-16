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
    void playedDoubleTile(std::string userInput);
    Tile play(bool humanTrainPlayable, bool computerTrainPlayable, bool mexicanTrainPlayable);
    void play2Test(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain);
protected:
private:

};
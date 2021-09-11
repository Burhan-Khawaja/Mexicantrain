#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <deque>
#include <string>
#include "Hand.h"
#include "Human.h"
#include "Computer.h"

class Round {
public:
    //why would we need this? can print hand in hand class. void printHand(Hand handToPrint);
    void instantiateDeck();
    void shuffleDeck();
    void dealTiles();
    void startRound();
    void whoGoesFirst();
    //remove engine tile from deck
    void removeEngineTile();
    //set engine tile as first tile for both trains.
    void setEngineTile();
//THESE 2 FUNCTIONS ARE INGAME CLASS, MIGHT HAVE TO FIGURE O UT WHERE THEY ARE BETTER SUITED.
    void resetEngineQueue();
    int getNextEngineValue();
    void startTurn();
    void printTrainAndEngine();
    void printHands();
    void playerHasTile(Tile tileToCheck);
    void tileFitsOnTrain(Tile tileToCheck);
    Tile drawFromBoneyard();
    //check human train for marker
    bool getHumanTrainMarker();
    bool getComputerTrainMarker();

protected:
private:
    //m_boneyard will contain all the cards, and shuffle t hem and disperse them to computer and player, and the remaining cards will be kept in the boneyard. 
    Hand m_boneyard;
    Hand m_computerHand;
    std::deque<int> engineQueue;
    Human humanPlayer;
    int engineInt;
    Computer computerPlayer;
};

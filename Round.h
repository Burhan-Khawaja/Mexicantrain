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
    //might not needd this idk what im doing
    Round();
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
    //function could be here but it could also fgit in player class.
    void tileFitsOnTrain(Tile tileToCheck);
    Tile drawFromBoneyard();
    //check human train for marker
    bool getHumanTrainMarker();
    bool getComputerTrainMarker();
    //1 function to check forr computer or player?
    //we could do 2 functions, checkHumansPlayableTrains(), and checkComputerPlayableTrains.
    bool checkOrphanDoubles();
    void checkHumansPlayableTrains();
    void checkComputerPlayableTrains();
    void resetPlayableTrains();
    bool getHumanTrainPlayable();
    bool getComputerTrainPlayable();
    bool getMexicanTrainPlayable();
    //verify that user enered a valid tile format.
    bool verifyTileChoice(std::string userInput);
    bool isDouble(Tile tileToCheck);
    //moved to player class for time being.
    bool playerHasMove();
    //BURBUR probably dont need these, delete after we refacotr idk what im doing
    int getComputerTrainEndNumber();
    int getHumanTrainEndNumber();
    int getMexicanTrainEndNumber();
    //this function will deal with the set of rules and things to do when a user plays a tile that is a double.
    void playedDoubleTile(std::string userInput);
protected:
private:
    //m_boneyard will contain all the cards, and shuffle t hem and disperse them to computer and player, and the remaining cards will be kept in the boneyard. 
    Hand m_boneyard;
    Hand m_computerHand;
    std::deque<int> engineQueue;
    int engineInt;
    Human humanPlayer;
    Computer computerPlayer;
    Train mexicanTrain;
    //these 3 booleans will dictate whether a player can place a tile on a train.
    bool humanTrainPlayable;
    bool computerTrainPlayable;
    bool mexicanTrainPlayable;
    bool humanTurn;
    bool computerTurn;
};






/*
things i need to add, a short list:
verify user has tile, verfy user entered valid tile.

*/
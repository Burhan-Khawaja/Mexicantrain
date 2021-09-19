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
    int startRound();
    void whoGoesFirst();
    //remove engine tile from deck
    void removeEngineTile();
    //set engine tile as first tile for both trains.
    void setEngineTile();
//THESE 2 FUNCTIONS ARE INGAME CLASS, MIGHT HAVE TO FIGURE O UT WHERE THEY ARE BETTER SUITED.
    void resetEngineQueue();
    int getNextEngineValue();
    int startTurn();
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

    //this function will deal with the set of rules and things to do when a user plays a tile that is a double.
    void playedDoubleTile(char userInput);
    bool validateTrainChoice(char userTrain,Tile userTile);
    int endRound();
    bool getWinner();
    void cleanData();

protected:
private:
    //m_boneyard will contain all the cards, and shuffle t hem and disperse them to computer and player, and the remaining cards will be kept in the boneyard. 
    Hand m_boneyard;
    std::deque<int> engineQueue;
    int engineInt;
    Human* humanPlayer;
    Computer* computerPlayer;
    Train mexicanTrain;
    //these 3 booleans will dictate whether a player can place a tile on a train.
    //BURBUR THESE WERE MOVED INTO THE PLAYER CLASS THEY SHOULD BE REMOVED AT A LATER DATE.
    bool humanTrainPlayable;
    bool computerTrainPlayable;
    bool mexicanTrainPlayable;
    bool humanTurn;
    bool computerTurn;
    bool computerWon;
    bool humanWon;
};
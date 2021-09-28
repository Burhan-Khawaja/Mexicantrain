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
   // ~Round();
    //why would we need this? can print hand in hand class. void printHand(Hand handToPrint);
    void instantiateDeck();
    void shuffleDeck();
    void dealTiles();
    int startRound(bool serialiedStart, int humanScore, int computerScore, int roundNumber);
    void whoGoesFirst(int humanScore, int computerScore);
    //remove engine tile from deck
    void removeEngineTile();
    //set engine tile as first tile for both trains.
    void setEngineTile();

    void resetEngineQueue();
    int getNextEngineValue();
    void setEngineValue(int engineVal);
    int startTurn(int humanScore, int computerScore, int roundNumber);
    Tile drawFromBoneyard();
    //check human train for marker
    bool getHumanTrainMarker();
    bool getComputerTrainMarker();
    void setTrainMarker(int whoseTrain);
    /* void resetPlayableTrains();
   
    bool getHumanTrainPlayable();
    bool getComputerTrainPlayable();
    bool getMexicanTrainPlayable();*/
    //verify that user enered a valid tile format.
    //bool verifyTileChoice(std::string userInput);
    //bool validateTrainChoice(char userTrain,Tile userTile);
    int endRound();
    bool getWinner();
    void cleanData();
    void setHand(std::deque<Tile> tiles, int whoseHand);
    void setTrain(std::deque<Tile> tiles, int whoseTrain);    
    char outputMenu(bool computerTurn);
    const std::vector<Tile> getHands(int whoseHand);
    const std::deque<Tile> getTrains(int whoseTrains);
    int getEngineInt();

    void setHumanTurn();
    void setComputerTurn();
    bool getHumanTurn();

protected:
private:

    Hand m_boneyard;
    std::deque<int> engineQueue;
    int engineInt;
    Human* humanPlayer;
    Computer* computerPlayer;
    Train mexicanTrain;
    bool humanTurn;
    bool computerTurn;

    bool computerWon;
    bool humanWon;
};
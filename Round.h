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
    Round();
    /* SELECTORS */

    int getNextEngineValue();

    bool getHumanTrainMarker();

    bool getComputerTrainMarker();

    bool getWinner();

    const std::vector<Tile> getHands(int whoseHand);

    const std::deque<Tile> getTrains(int whoseTrains);

    int getEngineInt();

    bool getHumanTurn();

    /* MUTATORS */

    void setComputerTurn();

    void setEngineValue(int engineVal);

    void setTrainMarker(int whoseTrain);

    void setHand(std::deque<Tile> tiles, int whoseHand);

    void setHumanTurn();

    void setTrain(std::deque<Tile> tiles, int whoseTrain);

    void setTrainEndNumbers();

    /* Helper Functions */

    void instantiateDeck();

    void shuffleDeck();

    void dealTiles();

    int startRound(bool serialiedStart, int humanScore, int computerScore, int roundNumber);
    
    void whoGoesFirst(int humanScore, int computerScore);

    void removeEngineTile();

    void resetEngineQueue();

    int startTurn(int humanScore, int computerScore, int roundNumber);

    Tile drawFromBoneyard();

    void cleanData();

    char outputMenu(bool computerTurn);
protected:
private:
    Train mexicanTrain;
    Hand m_boneyard;
    //deque of 9-0 in integers descending that we use to keep track of what engine is next
    std::deque<int> engineQueue;
    //current engine value
    int engineInt;
    //pointers to players. each player object has their train and hand in them
    Human* humanPlayer;
    Computer* computerPlayer;

    //boolean values to check whose turn it is
    bool humanTurn;
    bool computerTurn;
    //boolean values that dictate the winner
    bool computerWon;
    bool humanWon;
};
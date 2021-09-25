#pragma once
#include "Train.h"
#include "Hand.h"

#include <iostream>
#include <string>
class Player {
public:
    //BURBUR why is this virutal? doesnt need to be
    virtual void addTileToHand(Tile tileToAdd) = 0;
    virtual void addTileToTrain(Tile tileToAdd) = 0;    
    virtual int play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber,int engine) = 0;
    //old code, changed the function to take in the second tile from the train. virtual bool tileFitsOnTrain2(Tile tileToCheck, int engineInt) = 0;
    bool tileFitsOnTrain(Tile tileToCheck, int trainEndNumber);

    void printTrain();
    void printHand();
    void removeTileFromHand(int value1, int value2);
    bool getTrainMarker();
    void setTrainMarker();
    bool getOrphanDouble();
    //funciton to set orphan double to test code
    void setOrphanDouble() { playerTrain.setOrphanDouble(); };
    void resetOrphanDouble() { playerTrain.resetOrphanDouble(); }
    bool isTrainEmpty();
    Tile getFirstTrainTile();
    Tile getLastTrainTile();
    void setTrainEndNumber( int newEndNumber);
    int getTrainEndNumber();
    bool playerHasMove(int trainEndNumber);    
    bool existsValidMove(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain);
    Tile getFirstHandTile();
    //BURBUR this function is also in round
    bool verifyTileChoice(std::string userInput);
    bool validateTrainChoice(char userTrain);
    void playedDoubleTile(std::string userInput);    
    bool getHumanTrainPlayable();
    bool getComputerTrainPlayable();
    bool getMexicanTrainPlayable();
    bool checkOrphanDoubles(Player* oppositeTrain, Train mexicanTrain);
    int getHandSize();
    //check that player has the tile they selected
    bool hasTile(Tile userInputAsTile);
    bool noPlayableTiles(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard);
    int sumOfPips();
    void clearData();
    Tile playerTileChoice();
    const std::deque<Tile> getTrain();
    const std::vector<Tile> getHand();
    std::string findBestMove(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, std::vector<Tile>& bestTiles, std::vector<char>& trains);
    std::vector<Tile> getPlayableTiles(std::vector<Tile> playerHand, int trainEndNumber);
    void printGameState(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engineInt);
    std::string interpretBestMove(std::vector<Tile>& bestTiles, std::vector<char>& trains);
protected:    
    Train playerTrain;
    Hand playerHand;
    //BURBUR this is a test variable as of right now
    //this variable will store the integer of the tile that the next tile placed has to match.
    int trainLastNumber;    
    //these 3 booleans dictate weather the player can play on each train.
    bool humanTrainPlayable;
    bool computerTrainPlayable;
    bool mexicanTrainPlayable;
private:


};
#pragma once
#include "Train.h"
#include "Hand.h"

#include <iostream>
#include <string>
class Player {
public:

    Player();   
    /* *********************************************************************
    Function Name: play
    Purpose: This function implements the human and computers steps for a turn. 
        This function is virtual, so it is reimplemented in the computer and humans class.
    Parameters: 
        Player * humanPlayer - Stores all the information for the human player. 
                               Passed so we can manipulate and access its member variables if needed (ie- its train). passed by reference
        Player * computerPlayer - Stores all information of the computer player. 
                                passed into the function so we can manipulate and access its member variables. passed by reference
        Train& mexicanTrain - Train object that is passed by reference. This train will be changed when a user plays a tile on the mexican train.
        Hand& boneyard - Hand object passed by reference. Passed in so a player can take a tile if they do not have any playable tiles.
        int humanScore - humanScore, passed in so we can print it to the console for the user to see before their turns.
        int computerScore - computerScore, integer passed in so we can print it for  the user to see before their turns
        int roundNumber- integer that represents the round number so we can print it out for the user to see before their turn.
        int engine - this integer represets the engine value. we pass it in so when we print the game state, we can print out the engine.
    Return Value: integer. -10 is our value for the user wanting to save the game, and positive integer represents the losers total PIPS left in their hands.
    Algorithm: virtual function so it depends on the derived object that calls it
    Assistance Received: None.
    ********************************************************************* */
    virtual int play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engine) = 0;

    /* *********************************************************************
    Function Name: addTileToTrain
    Purpose: add a tile to a train. Virtual function since the player and computer trains add tiles to opposite ends.
    Parameters:
        Tile tileToAdd - The tile that the user wants to add to their train
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    virtual void addTileToTrain(Tile tileToAdd) = 0;

    void addTileToHand(Tile tileToAdd);
    /* SELECTORS */
    bool const getTrainMarker();
    bool const getOrphanDouble();
    int const getTrainEndNumber();
    bool const getHumanTrainPlayable();
    bool const getComputerTrainPlayable();
    bool const getMexicanTrainPlayable();
    int const getHandSize();
    const std::deque<Tile> getTrain();
    const std::vector<Tile> getHand();

    /* MUTATORS */
    void setTrainMarker();
    void setHumanTrainPlayable();
    void setComputerTrainPlayable();
    void setOrphanDouble();
    void setTrainEndNumber(int newEndNumber);

    /* Helper Functions */
    void resetTrainMarker();
    bool tileFitsOnTrain(Tile tileToCheck, int trainEndNumber);
    void printTrain();
    void printHand();
    void removeTileFromHand(int value1, int value2);
    void resetOrphanDouble();
    bool playerHasMove(int trainEndNumber);    
    bool existsValidMove(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain);      
    bool verifyTileChoice(std::string userInput);
    bool validateTrainChoice(char userTrain);
    bool checkOrphanDoubles(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain);
    bool hasTile(Tile userInputAsTile);
    bool noPlayableTiles(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard);
    int sumOfPips();
    void clearData();
    Tile playerTileChoice();
    void findBestMove(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, std::vector<Tile>& bestTiles, std::vector<char>& trains);
    std::vector<Tile> getPlayableTiles(std::vector<Tile> playerHand, int trainEndNumber); 
    void printGameState(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engineInt);
    std::string interpretBestMove(std::vector<Tile>& bestTiles, std::vector<char>& trains);

protected:   
    //stores the tiles on the players train
    Train playerTrain;
    //stores the tiles in the players hand
    Hand playerHand;
    //this integer stores the last number on the train, that the next tile played has to match to fit on the train
    int trainLastNumber;    
    //these 3 booleans dictate whether the player can play on each train.
    bool humanTrainPlayable;
    bool computerTrainPlayable;
    bool mexicanTrainPlayable;
private:


};
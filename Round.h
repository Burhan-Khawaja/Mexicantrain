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
    /* *********************************************************************
    Function Name: Round
    Purpose: Set default values of Round member variables.
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    Round();

    /* *********************************************************************
    Function Name: instantiateDeck
    Purpose: Create a double nine set, containing 55 tiles.
    Parameters: None
    Return Value: None
    Algorithm: 1) while integer i is less then 10,
               2)create integer j = i. while j is less then 10
                   2a)create a Tile object with values i,j passed in, and add it to the boneyard
    Assistance Received: None.
    ********************************************************************* */

    void instantiateDeck();

    /* *********************************************************************
    Function Name: shuffleDeck
    Purpose: shuffle the deck so that every tile is randomly placed
    Parameters: None
    Return Value: None
    Algorithm: 1) for every tile in the deck:
                    1a) generate a random number that is between 0 and the size of the deck, and store it in the variable randomNum
                    1b) Create a temporary tile called tmpTile that stores the current tile we are on
                    1c) Set the current tile we are on to be equal to the tile at the position of randomNum
                    1d) Set the tile at position randomNum to be equal to our tmpTile 
    Assistance Received: None.
    ********************************************************************* */
    void shuffleDeck();

    /* *********************************************************************
    Function Name: dealTiles
    Purpose: deal the tiles to the players.
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void dealTiles();

    /* *********************************************************************
    Function Name: startRound
    Purpose: setup the variables for the round
    Parameters: serialiedStart boolean value that is used to tell us if we are starting 
                        a game fresh and need to create data, or if we have loaded a game from a file
               humanScore- Integer value that is passed in so we are able to print out the human players score to the console
               computerScore- Integer value passed in so we can print computer's score to the console
               roundNumber - Integer value passed in so we can print the round number to the console.
    Return value: Integer value that represents the round losers pip value of the tiles left in their hand.
                  Can also be a negative number for certain codes (ie - -10 is the code to save)
    Assistance Received: None.
    ********************************************************************* */
    int startRound(bool serialiedStart, int humanScore, int computerScore, int roundNumber);
    
    /* *********************************************************************
    Function Name: whoGoesFirst
    Purpose: see which player goes first
    Parameters: humanScore - integer value that represents the score of the human.
                computerScore- int that holds the score of the computer
    Return value: None
    Algorithm:  1) If human has a lower score then the computer, human goes first
                2) else if computer has lower score then human, computer goes firsts
                3) else, a random number 1 or 2 is generated and the user guesses the number. If they guess correctly they go first.
    Assistance Received: None.
    ********************************************************************* */
    void whoGoesFirst(int humanScore, int computerScore);

    /* *********************************************************************
    Function Name: removeEngineTile
    Purpose: remove the tile that will be the engine for the round from the deck
    Parameters: None
    Return value: None
    Assistance Received: None.
    ********************************************************************* */
    void removeEngineTile();

    /* *********************************************************************
    Function Name: setTrainEndNumbers
    Purpose: Initialize the train's end numbers to be the engine int.
    Parameters: None
    Return value: None
    Assistance Received: None.
    ********************************************************************* */
    void setTrainEndNumbers();

    /* *********************************************************************
    Function Name: resetEngineQueue
    Purpose: reset the queue that stores the engine values so that the queue will hold 9-0 in descending order.
    Parameters: None
    Return value: None
    Assistance Received: None.
    ********************************************************************* */
    void resetEngineQueue();

    /* *********************************************************************
    Function Name: getNextEngineValue
    Purpose: Get the integer for the next engine value
    Parameters: None
    Return value: integer that is the next engine value
    Assistance Received: None.
    ********************************************************************* */
    int getNextEngineValue();

    /* *********************************************************************
    Function Name: setEngineValue
    Purpose: set the engine value to a certain integer we pass in. This is used in serialization to begin with the proper engine
    Parameters: engineVal, integer that is the number we want our engine to be.
    Return value: None
    Assistance Received: None.
    ********************************************************************* */
    void setEngineValue(int engineVal);

    /* *********************************************************************
    Function Name: startTurn
    Purpose: Start both computer and players turn until the round is over.
    Parameters: humanScore- integer value that stores the human players score. Passed so we can print it out before every turn
                computerScore- integer value that stores the computer players score. Passed so we can print it out before every turn
                roundNumber - integer value that stores the current round number. passed so we can print it before every turn
    Return value: Integer value  
    Assistance Received: None.
    ********************************************************************* */
    int startTurn(int humanScore, int computerScore, int roundNumber);

    /* *********************************************************************
    Function Name: drawFromBoneyard
    Purpose: take the top tile from the boneyard, and return it
    Parameters: None
    Return value: Tile object that represents the top tile of the boneyard
    Assistance Received: None.
    ********************************************************************* */
    Tile drawFromBoneyard();

    /* *********************************************************************
    Function Name: getHumanTrainMarker
    Purpose: check if the human players train has a marker
    Parameters: None
    Return value: Bool, true if the human train has a marker on it, false if it doesnt
    Assistance Received: None.
    ********************************************************************* */
    bool getHumanTrainMarker();

    /* *********************************************************************
    Function Name: getComputerTrainMarker
    Purpose: check if the cpu's train has a marker
    Parameters: None
    Return value: Bool, true if the cpu train has a marker on it, false if it doesnt
    Assistance Received: None.
    ********************************************************************* */
    bool getComputerTrainMarker();

    /* *********************************************************************
    Function Name: setTrainMarker
    Purpose: set a player trains marker
    Parameters: whoseTrain, integer value that represents whose train we turn the marker on for. 
                0 is computer, 1 is human, 2 is mexican.
    Return value: void
    Assistance Received: None.
    ********************************************************************* */
    void setTrainMarker(int whoseTrain);

    /* *********************************************************************
    Function Name: setHand
    Purpose: set a players hand to equal a deque of tiles, used in seralization
    Parameters: tiles, deque of tiles passed in by value that we will loop through and add all values to a players hand
                whoseHand, integer value that represents whose hand we fill
                0 is computer, 1 is human, 2 is mexican.
    Return value: void
    Assistance Received: None.
    ********************************************************************* */
    void setHand(std::deque<Tile> tiles, int whoseHand);

    /* *********************************************************************
    Function Name: setTrain
    Purpose: set a players train to equal a deque of tiles, and set their end numbers to the corresponding value. used in seralization
    Parameters: tiles, deque of tiles passed in by value that we will loop through and add all values to a players train
                whoseHand, integer value that represents whose train we fill
                0 is computer, 1 is human, 2 is mexican.
    Return value: void
    Assistance Received: None.
    ********************************************************************* */
    void setTrain(std::deque<Tile> tiles, int whoseTrain);

    /* *********************************************************************
    Function Name: getWinner
    Purpose: gets the winner of a round
    Parameters: None
    Return value: bool, true if the human won, false if the computer won
    Assistance Received: None.
    ********************************************************************* */
    bool getWinner();

    /* *********************************************************************
    Function Name: cleanData
    Purpose: clean all the round data so we can play a new round with no lingering tiles
    Parameters: None
    Return value: none
    Assistance Received: None.
    ********************************************************************* */
    void cleanData();

    /* *********************************************************************
    Function Name: outputMenu
    Purpose: Output the menu for the player to choose to save the game, make a move, ask for help, or quit
    Parameters: computerTurn, boolean value thats passed in because we dont have the computer ask for help
    Return value: char, which is a character that corresponds to what the user chose.
    Assistance Received: None.
    ********************************************************************* */
    char outputMenu(bool computerTurn);

    /* *********************************************************************
    Function Name: getHands
    Purpose: retrive a players hand as a vector. Needed to save the game
    Parameters: whoseHand, integer value thats passed in so we can check whose hand we need.
                    0 is computer, 1 is human, 2 is mexican.
    Return value: vector of Tiles that is a copy of the players hand.
    Assistance Received: None.
    ********************************************************************* */
    const std::vector<Tile> getHands(int whoseHand);

    /* *********************************************************************
    Function Name: getTrains
    Purpose: retrive a players train as a deque. Needed to save the game
    Parameters: whoseHand, integer value thats passed in so we can check whose hand we need.
                    0 is computer, 1 is human, 2 is mexican.
    Return value: vector of Tiles that is a copy of the players train.
    Assistance Received: None.
    ********************************************************************* */
    const std::deque<Tile> getTrains(int whoseTrains);

    /* *********************************************************************
    Function Name: getEngineInt
    Purpose: retrive the value of the engine
    Parameters: None
    Return value: integer value that is the value of the current rounds engine tile
    Assistance Received: None.
    ********************************************************************* */
    int getEngineInt();

    /* *********************************************************************
    Function Name: setHumanTurn
    Purpose: set the humans turn to true, and compuers turn to false
    Parameters: None
    Return value: None
    Assistance Received: None.
    ********************************************************************* */
    void setHumanTurn();

    /* *********************************************************************
    Function Name: setComputerTurn
    Purpose: set the computers turn to true, and the humans to false
    Parameters: None
    Return value: None
    Assistance Received: None.
    ********************************************************************* */
    void setComputerTurn();

    /* *********************************************************************
    Function Name: getHumanTurn
    Purpose: check if its currently the humans turn. if it is not, then its the computers turn
    Parameters: None
    Return value: bool, true if it is the computers turn , false if it is not
    Assistance Received: None.
    ********************************************************************* */
    bool getHumanTurn();

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
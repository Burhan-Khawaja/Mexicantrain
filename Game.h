#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <fstream>
#include "Round.h"


class Game {
public:
    /* *********************************************************************
    Function Name: Game
    Purpose: Set default values of Game member variables.
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    Game();

    /* *********************************************************************
    Function Name: getRoundNumber
    Purpose: get what round we are on
    Parameters: None
    Return Value: integer value that is the round number we are on
    Assistance Received: None.
    ********************************************************************* */
    int const getRoundNumber();

    /* *********************************************************************
    Function Name: setRoundNumber
    Purpose: set the round number. used for serializationn
    Parameters: roundNum, integer that we will set the roundnumber to 
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void setRoundNumber(int roundNum);

    /* *********************************************************************
    Function Name: getHumanScore
    Purpose: retrieve human score value
    Parameters: None
    Return Value: integer value that represents the humans score
    Assistance Received: None.
    ********************************************************************* */ 
    int const getHumanScore();

    /* *********************************************************************
    Function Name: setHumanScore
    Purpose: set the human score value. used in serialization when we load a game in
    Parameters: hScore, integer value that is the human score we want to set it to 
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void setHumanScore(int hScore);

    /* *********************************************************************
    Function Name: getComputerScore
    Purpose: get computer's score
    Parameters: None
    Return Value: integer value that is the computers current score
    Assistance Received: None.
    ********************************************************************* */
    int getComputerScore();

    /* *********************************************************************
    Function Name: setComputerScore
    Purpose: set computer's score
    Parameters: cScore, integer value that we will set the computer's score to equal.
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void setComputerScore(int cScore);

    /* *********************************************************************
    Function Name: playGame
    Purpose: Start the game, and deal with the outcome of the game
    Parameters: None
    Return Value: None
    Algorithm: 1) Ask if user wants to start a fresh game, or load a game.
               2) If the user wants to load a game, then load the game from whatever file they mention, and start the round.
               3) If the player does not want to load a game, then initialize all the values by default and start the round.
               4) When the user finishes the round, check if the value returned by the round class is -10. If it is, save the game
               5) if the human player won, add the value returned to the computers sore
                  5a)else, add the value to the humans score
               6) Prompt the user if they want to play again.
    Assistance Received: None.
    ********************************************************************* */
    void playGame();

    /* *********************************************************************
    Function Name: addComputerScore
    Purpose: add to the computer's score
    Parameters: pipVal, integer passed by value that is the amount we wish to add the computers score by
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void addComputerScore(int pipVal);

    /* *********************************************************************
    Function Name: addHumanScore
    Purpose: add to the human's score
    Parameters: pipVal, integer passed by value that is the amount we wish to add the human's score by
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void addHumanScore(int pipVal);

    /* *********************************************************************
    Function Name: playAgainPrompt
    Purpose: ask the user if they want to play again, deal with their input
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void playAgainPrompt();

    /* *********************************************************************
    Function Name: outputWinner
    Purpose: check who won the game, and output the winner
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void outputWinner();

    /* *********************************************************************
    Function Name: loadGame
    Purpose: load the game from a file
    Parameters: None
    Return Value: None
    Algorithm: 
            1) Ask user for the name of file
            2) Open the file, and begin to read the file line by line
            3) While we read valid lines: 
                3a) If the first word we read is round:
                    3aa) read in the second word, and set the roud number to that value
                3b) If the first word we read is Computer
                    3ba) set the boolean computerData to true, and humanData to false.
                3c) If the first word is Human
                    3ca) set the boolean humanData to true, and computerData to false
                3d) If the first word is Score
                    3da) if computerData is true, set the computer score to the second word read in
                    3db) else set humanData to the 2nd word read in
                3e) If the first word is Hand
                    3ea) parse the entire line, and return a deque of all the tiles in the line
                    3eb) if computerData is true, add all the tiles to our hand
                    3ec) else add the tiles to the human players hand
                3f) If the first word is Train                    
                    3fa) parse the entire line, and return a deque of all the tiles in the line
                    3fb) set the trains marker if it needs to be set, and remove the back tile off because it is the engine tile
                    3fc) if computer Data is true, 
                    3fd) reverse the deque
                    3fe) add all the tiles to the deque.
                    3fg)else if computer data is false, add the tiles to the humans train
                3g) If the first word is Mexican
                    3ga) set computer and humandata booleans false
                    3gb) parse the line of tiles, and store all the tiles on the line into a deque
                    3gc) add the deque of tiles to the mexican train
                3h) If the first word is Boneyard
                    3ha) parse the line of tiles, store all the tiles in a deque
                    3hb) add the tiles in the deque to the boneyard
                3i) If the first word is Next
                    3ia)find the second word. if its computer, set the computers turn to tru
                    3ib)else, set the humans turn to true.
    Assistance Received: None.
    ********************************************************************* */
    void loadGame();   

    /* *********************************************************************
    Function Name: saveGame
    Purpose: save the gaame to a file
    Parameters: None
    Return Value: None
    Algorithm:
            1) Ask user for name of file to save as
            2) create the save file
            3) write the correct round number to the file
            4) retrieve the hands of the computer, and save it to the file
            5) retrieve the trains of the computer, and save it to the file
            6) repeat step  4 and 5 for human player
            7) print mexican train to file
            8) print boneyuard to the file
            9) print next player to the file
    Assistance Received: None.
    ********************************************************************* */
    void saveGame();


    /* *********************************************************************
    Function Name: setHand
    Purpose: set a players hand to equal a vector passed in. used to load a game from a file
    Parameters: tiles - deque of Tiles passed in by value, all Tiles in the deque are added to players hand, 
                whoseHand - Integer value that determines where we are adding this deque.
                            0 is computer, 1 is human, 2 is boneyard.
    Return Value: None
    Algorithm:
                1- For every tile in Tiles
                    1a) if whoseHand == 0, add tile to computers hand
                    1b) else if whoseHand == 1, add tile to human's hand
                    1c) else add tile to boneyard
    Assistance Received: None.
    ********************************************************************* */
    void setHand(std::deque<Tile> tiles, int whoseHand);

    /* *********************************************************************
    Function Name: parseLineOfTiles
    Purpose: take in an entire line from a file, and create a dequue of Tiles from that line.
    Parameters: input string that represents the line from the file.,
                setMarker- boolean value that is passed by value. If we encounter a 'M' character while we parse the line,
                            that means that the train has a marker. and we will set the boolean to true so that we can set the 
                            train objects marker to true as well.
    Return Value: None
    Algorithm:
                1) Read the first word of the line (It will always be useless for us, so we disregard it
                2) Read the second word
                    2a) if the second word is Train, do nothing
                    2b) else if the second word is "M", set setMarker to true.
                    2c) else, get the first and third elements of the word, and create a tile and add it to our list of tile
                3) while we can read in words from the line
                    3a) If we read an "M", set the boolean setMarker to true. return the deque of tiles (this will be the last value on the line.
                    3b) get the first and third characters from the line, and add them to the deque of tiles.
                4) Return the deque of tiles.
                    Assistance Received: None.
    ********************************************************************* */
    std::deque<Tile> parseLineOfTiles(std::string input, bool& setMarker);

    /* *********************************************************************
    Function Name: parseLineOfTiles
    Purpose: take in an entire line from a file, and create a dequue of Tiles from that line.
    Parameters:  file- an ofstream object that is the file we are currently saving the game to. Passed by reference so we are able to change it
                       tiles, Deque of tiles passed by reference so we can add the tiles to the file. 
                       This function empties the deque after we have printed them to the file.
    Return Value: None
    ********************************************************************* */
    void printDequeToFile(std::ofstream& file, std::deque<Tile>& tiles);

protected:
private:
    //stores the current round number
    int roundNumber;
    //stores the human score
    int humanScore;
    //stores the computer score
    int computerScore;
    //round object that stores all the information required to play a round (human/player objects, mexican train, boneyard, etc)
    Round round;
    //deque that stores the values of the engine unit for every round ( 9-0 in descending order).
    std::deque<int> engineQueue;
};
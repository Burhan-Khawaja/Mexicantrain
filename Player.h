#pragma once
#include "Train.h"
#include "Hand.h"

#include <iostream>
#include <string>
class Player {
public:

    /* *********************************************************************
    Function Name: Player
    Purpose: Set default values of Player member variables.
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
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
    Function Name: addTileToHand
    Purpose: Add a tile to a players hand. used when they pick a card from a boneyard
    Parameters:
        Tile tileToAdd - The tile that the user picked from the boneyard and needs to add into their hand
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void addTileToHand(Tile tileToAdd);

    /* *********************************************************************
    Function Name: addTileToTrain
    Purpose: add a tile to a train. Virtual function since the player and computer trains add tiles to opposite ends.
    Parameters:
        Tile tileToAdd - The tile that the user wants to add to their train
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    virtual void addTileToTrain(Tile tileToAdd) = 0;    

    /* *********************************************************************
    Function Name: tileFitsOnTrain
    Purpose: Check if a tile fits on a certain train, based on that trains last number
    Parameters:
        Tile tileToCheck-- Tile object passed by value that we want to check if it fits on a train. 
        int trainEndNumber-- integer value that represents the last number of a train, that a tile has to match to be added onto that train.
    Return Value: None
    Algorthm: 
        1)Check if the tile's first number is equal to the trains end number.
            1a)if it is, return true.
        2)else, check if the tiles second number is equal to the trains end number.
            2a)if it is, return true
        3)return false.
    Assistance Received: None.
    ********************************************************************* */
    bool tileFitsOnTrain(Tile tileToCheck, int trainEndNumber);

    /* *********************************************************************
    Function Name: printTrain
    Purpose: print a train to the console.
    Parameters:None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void printTrain();

    /* *********************************************************************
    Function Name: printHand
    Purpose: print a players hand to the console.
    Parameters:None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void printHand();

    /* *********************************************************************
    Function Name: removeTileFromHand
    Purpose: Remove a tile from a players hand.
    Parameters: 
        int value1 - first value of the tile we want to remove
        int value2 - second value of the tile we want toremove
    Return Value: None
    Algorithm:  1)Create a tile with the 2 values given as the tiles numbers
                2)call the erase function of the vector and search the array from beginning to end for the tile we created in step 1
                    when the tile is found, it will be removed.
    Assistance Received: None.
    ********************************************************************* */
    void removeTileFromHand(int value1, int value2);

    /* *********************************************************************
    Function Name: : getTrainMarker
    Purpose: check if a player train has a marker on it.
    Parameters: None
    Return Value: True if there is a maker, false otherwise.
    Assistance Received: None.
    ********************************************************************* */
    bool getTrainMarker();

    /* *********************************************************************
    Function Name: : setTrainMarker
    Purpose: Set a players train marker to true
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void setTrainMarker();

    /* *********************************************************************
    Function Name: : resetTrainMarker
    Purpose: Set a players train marker to false
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */

    void resetTrainMarker();
    /* *********************************************************************
    Function Name: : getOrphanDouble
    Purpose: Checks a players train and looks for an orphan double.
    Parameters: None
    Return Value: true ifthe players train has an orphan double, fale if it doesnt.
    Assistance Received: None.
    ********************************************************************* */
    bool getOrphanDouble();


    /* *********************************************************************
    Function Name: : setOrphanDouble
    Purpose: set a player trains orphan double boolean to true.
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void setOrphanDouble();

    /* *********************************************************************
    Function Name: : resetOrphanDouble
    Purpose: Reset a player trains orphan double, setting it back to false. used after they plan on the orphan double
    Parameters: None
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void resetOrphanDouble();

    /* *********************************************************************
    THIS FUNCTION isTrainEmpty IS COMMENTED OUT SINCE WE DO NOT USE IT.
    ********************************************************************* */
    //bool isTrainEmpty();

    /* *********************************************************************
    THESE FUNCTIONS ARE COMMENTED OUT SINCE HTEY ARE NOT USED.
    Tile getFirstTrainTile();

    Tile getLastTrainTile();    
    ********************************************************************* */

    /* *********************************************************************
    Function Name: : setTrainEndNumber
    Purpose: Set a trains end number to the new value passed to the function. 
             The trains end number is the number that is left "hanging" that new tiles have to match.
    Parameters: newEndNumber, integer that is the new train's end number.
    Return Value: None
    Assistance Received: None.
    *********************************************************************  */
    void setTrainEndNumber(int newEndNumber);

    /* *********************************************************************
    Function Name: : getTrainEndNumber
    Purpose: get the end number of a train that tiles must match in order to be added to that train
    Parameters: None
    Return Value: integer value that represents the last number on the train that must be matched.
    Assistance Received: None.
    *********************************************************************  */
    int getTrainEndNumber();

    /* *********************************************************************
    Function Name: : playerHasMove
    Purpose: Check if a player has a valid move on a certain train.
    Parameters: trainEndNumber, which is the end number of a train, and we check all our tiles against it and see if we have a match.
    Return Value: boolean value. True if we have a move, false if we dont.
    Algorithm: 
                1)Loop through the players hand.
                2)for every tile in the players hand, if the first number of the tile matches trainEndNumber, return true
                3)if the second number of the tile matches the trainEndNumber, return true
                4)after we have looped through the entire hand, return false.
    Assistance Received: None.
    *********************************************************************  */
    bool playerHasMove(int trainEndNumber);    

    /* *********************************************************************
    Function Name: : existsValidMove
    Purpose: Check if a player has a valid move on any train at all. This function will call playerHasMove for each train that the player can play on.
    Parameters: 
        Player* humanPlayer- a Player object passed by reference that stores all the human player data. This parameter is not modified by the function.
            This variable is included so we can access its train to check if there are valid moves, and see what trains are playable
        Player* computerPlayer- a Player object passed by reference that stores all the computer player's data. This parameter is not modified by the function.
            This variable is included so we are able to access its train to see if we hav valid moves, and check what trains are playable.
        Train& mexicanTrain- Train object passed by reference. not modified, and used to see if any tiles we have matches its end number
    Return Value: boolean value. True if we have a move, false if we dont.
    Algorithm:
                2)Check if the humanTrainBoolean is true. if it is, check if we have a move on it.
                3)Check if the computerTrainBoolean is true. If it is, check if we have a valid move on it 
                4)Check if the mexicanTrainBoolean is true. If it is, check if we have a valid move on it.
                We check if we have a valid move on the train by calling playerHasMove(), and checking if they have a move on that train
                1)Loop through the players hand.
                2)for every tile in the players hand, if the first number of the tile matches trainEndNumber, return true
                3)if the second number of the tile matches the trainEndNumber, return true
                4)after we have looped through the entire hand, return false.

    Assistance Received: None.
    *********************************************************************  */
    bool existsValidMove(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain);
    //Tile getFirstHandTile();
        
    /* *********************************************************************
    Function Name: : verifyTileChoice
    Purpose: Check if a player entered valid input for a tile
    Parameters: userInput, string which is the texxt that the user entered as a value for a tile
    Return Value: boolean value. True if the user entered a valid tile, false if they didnt
    Algorithm:
                1)If the length of the string is more then 3, return false
                2)If the length of the string is less then or equal to 2, return false
                3)if the first character or the third character are not numbers, return false.
                4)if the second character is not a '-', return false
                5)return true
    Assistance Received: None.
    *********************************************************************  */
    bool verifyTileChoice(std::string userInput);

    /* *********************************************************************
    Function Name: : validateTrainChoice
    Purpose: Check if the user entered a valid train,  and if they can actually play on that train.
    Parameters: userTrain, Character which the user enters to signal what train they want to play on
    Return Value: boolean value. True if the user entered a valid train and can play on it, false if they didnt
    Assistance Received: None.
    *********************************************************************  */
    bool validateTrainChoice(char userTrain);
    bool getHumanTrainPlayable();
    void setHumanTrainPlayable();
    bool getComputerTrainPlayable();
    void setComputerTrainPlayable();
    bool getMexicanTrainPlayable();
    bool checkOrphanDoubles(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain);
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
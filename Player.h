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

    /* *********************************************************************
    Function Name: : getHumanTrainPlayable
    Purpose: Check if the player object can play on the human train
    Parameters: None
    Return Value: True if the player can play on the human train, false if it cant
    Assistance Received: None.
    *********************************************************************  */
    bool getHumanTrainPlayable();

    /* *********************************************************************
     Function Name: : setHumanTrainPlayable
     Purpose: set the boolean humanTrainPlayable value to true.
     Parameters: None
     Return Value: None
     Assistance Received: None.
     *********************************************************************  */
    void setHumanTrainPlayable();

    /* *********************************************************************
     Function Name: : getComputerTrainPlayable
     Purpose: get the computerTrainPlayable boolean which tells us if the player object can play on that train
     Parameters: None
     Return Value: a boolean value, true if the player can play on the train, false if they cant
     Assistance Received: None.
     *********************************************************************  */
    bool getComputerTrainPlayable();

    /* *********************************************************************
     Function Name: : setComputerTrainPlayable
     Purpose: set the computerTrainPlayable boolean to true, which lets the player play on that train
     Parameters: None
     Return Value: void
     Assistance Received: None.
     *********************************************************************  */
    void setComputerTrainPlayable();

    /* *********************************************************************
     Function Name: : getMexicanTrainPlayable
     Purpose: get the mexicanTrainPlayable boolean, which lets us know if we can play on the mexican train
     Parameters: None
     Return Value: bool, true if we are allowed to play on the mexican train
     Assistance Received: None.
     *********************************************************************  */
    bool getMexicanTrainPlayable();

    /* *********************************************************************
     Function Name: : checkOrphanDoubles
     Purpose: Check if any train has an orphan double on it.
     Parameters: Player* humanPlayer -Stores human player data, passed by reference
                 Player* computerPlayer- stores computer player data, passed by reference
                 Train mexicanTrain - stores the mexican train data, passed by value
     Return Value: bool, true if there exists an orphan double
     Algorithm: 1)create an orphanDouble boolean that tracks the existence of orphans.
                1) check if there is any orphan double at all
                    1a) if there is an orphan double, set all playable train variables to false.
                2) check human/player/mexican train for orphan doubles. 
                    2a) if any train has an orphan double, set them playable and set orphanDouble bool to true
                3) return orphanDouble
     Assistance Received: None.
     *********************************************************************  */
    bool checkOrphanDoubles(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain);

    /* *********************************************************************
     Function Name: : getHandSize
     Purpose: Check the size of a players hand
     Parameters: None
     Return Value: the size of the players hand, an integer
     Assistance Received: None.
     *********************************************************************  */
    int getHandSize();

    /* *********************************************************************
     Function Name: : hasTile
     Purpose: Check to make sure a player has a tile that they entered
     Parameters: userInputAsTile, Tile object passed by value that is used to check if the player has that tile.
     Return Value: Boolean value, true if a player has the tile in their hand
     Assistance Received: None.
     *********************************************************************  */
    bool hasTile(Tile userInputAsTile);

    /* *********************************************************************
     Function Name: : noPlayableTiles
     Purpose: deals with the correct ruleset when a player has no playable tile
     Parameters: Player* humanPlayer -Stores human player data, passed by reference
                 Player* computerPlayer- stores computer player data, passed by reference
                 Train mexicanTrain - stores the mexican train data, passed by value
     Return Value: Boolean value, true if the tile the player drew from the boneyard is playable, false if it is not
     Algorithm: 1)check if the boneyard is empty
                    1a) if it is, output that its empty, add a marker to player train, return false
                2)else, get the top tile of the boneyard.
                3) remove that tile from the boneyard
                4)add the tile to players hand.
                5)check if the user has a valid move after adding the boneyard tile to their hand
                6)if they dont have a valid mo ve, set a marker on their train and return false
                7)else, return true.
     Assistance Received: None.
     *********************************************************************  */
    bool noPlayableTiles(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard);

    /* *********************************************************************
     Function Name: : sumOfPips
     Purpose: returns the sum of pips that a player has left in their hands
     Parameters: None
     Return Value: integer value that is the sum of the pips left
     Assistance Received: None.
     *********************************************************************  */
    int sumOfPips();

    /* *********************************************************************
     Function Name: : clearData
     Purpose: clears the data player hand and player train data to get it ready for next round
     Parameters: None
     Return Value: None
     Assistance Received: None.
     *********************************************************************  */
    void clearData();

    /* *********************************************************************
     Function Name: : playerTileChoice
     Purpose: ask user for a tile, and verify that it is valid
     Parameters: None
     Return Value: Tile, which is a tile object that is based on what the user entered.
     Assistance Received: None.
     *********************************************************************  */
    Tile playerTileChoice();

    /* *********************************************************************
     Function Name: : getTrain
     Purpose: get the players train
     Parameters: None
     Return Value: const deque<Tile>, which is the deque of all the tiles on a train
     Assistance Received: None.
     *********************************************************************  */
    const std::deque<Tile> getTrain();

    /* *********************************************************************
     Function Name: : getHand
     Purpose: get the players hand
     Parameters: None
     Return Value: const vector<Tile>, which is the vector of all the tiles on a train
     Assistance Received: None.
     *********************************************************************  */
    const std::vector<Tile> getHand();

    /* *********************************************************************
     Function Name: : findBestMove
     Purpose: find the best move a player has
     Parameters: Player * humanPlayer- Player object that stores data for human player, passed by reference
                 Player * computerPlayer- Player object that stores data for computer player, passed by reference
                 Train& mexicanTrain- Train object passed by reference, stores information about mexican train
                 Hand& boneyard-Hand object passed by reference, stores the boneyard data
                 std::vector<Tile>& bestTiles- a vector passed by reference. This vector is empty intially, and will store
                                               the best tiles for the user to play.
                 std::vector<char>& trains-a vector passed by reference. This vector is empty intially, and will store
                                             the corresponding trains the user will play on.
     Return Value: None
     Algorithm:
                 0-create 3 vector of Tiles that store what tiles we can play on mexican, human, and computer train, 
                    and 3 more vectors of Tiles that store the doubles we can play
                 1-Create new hand, tempPlayerHand that we store players hand into so we can manipulate it
                 2-Store player hand in tempPlayerHand
                 3-while true
                    3a- if mexican train is playable, get all the playable tiles on that train and place them into mexicanPlayableTiles vector
                    3b- if computer train is playable, get all the playable tiles on that train and place them into computerPlayableTiles vector
                    3c- if human train is playable, get all the playable tiles on that train and place them into humanPlayableTiles vector
                    3d- store all the doubles into their respective doubles vector
                    3e- If we can play on the mexican train, and the mexicanDoubles vector isnt empty, and we have played less then 2 doubles, 
                        add the first double to bestTiles vector. remove the tile from out temporary hand, and restart from step 3.
                    3f- If we can play on the human train, and the mexicanDoubles vector isnt empty, and we have played less then 2 doubles, 
                        add the first double to bestTiles vector. remove the tile from out temporary hand, and restart from step 3.    
                    3g- If we can play on the computer train, and the mexicanDoubles vector isnt empty, and we have played less then 2 doubles, 
                        add the first double to bestTiles vector. remove the tile from out temporary hand, and restart from step 3.
                    3h- Repeat steps 3e -3g, except this time for the vector that stores the non double tiles.
                    3i- If we play a tile that is not a double, return from the function
                    3j- when we have played a non double tile, or have played 3 tiles return from the function.
     Assistance Received: None.
     *********************************************************************  */
    void findBestMove(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, std::vector<Tile>& bestTiles, std::vector<char>& trains);

    /* *********************************************************************
     Function Name: : getPlayableTiles
     Purpose: get the players hand
     Parameters: playerHand, which is a vector of tiles that stores all the tiles in a players hand passed by value
                 int trainEndNumber, an integer that represents the last number on a train that a tile must match
     Return Value: std::vector<Tile>, a vector of tiles that stores all the playable tiles on the given train
     Algorithm: 1)Loop through playerHand
                2)if the tile's first number is equal to the trains end number, add the tile to vector we return
                3)else if the tile's second number is equal to the trains end number, add the tile to vector we return
                4)once we have looped through the entire hand, return the vector of playable tiles.
     Assistance Received: None.
     *********************************************************************  */
    std::vector<Tile> getPlayableTiles(std::vector<Tile> playerHand, int trainEndNumber);
   
    /* *********************************************************************
    Function Name: printGameState
    Purpose: This function prints the current state of the game, including the round numbers, scores, hands, trains, and decks.
    Parameters:
        Player * humanPlayer - Stores all the information for the human player.  passed by reference
        Player * computerPlayer - Stores all information of the computer player. passed by reference
        Train& mexicanTrain - Train object that is passed by reference that stores the mexican train tiles. 
        Hand& boneyard - Hand object passed by reference. stores the boneyard and all the tiles in it
        int humanScore - humanScore, passed in so we can print it to the console for the user to see before their turns.
        int computerScore - computerScore, integer passed in so we can print it for  the user to see before their turns
        int roundNumber- integer that represents the round number so we can print it out for the user to see before their turn.
        int engine - this integer represets the engine value. we pass it in so when we print the game state, we can print out the engine.
    Return Value: None
    Assistance Received: None.
    ********************************************************************* */
    void printGameState(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engineInt);

    /* *********************************************************************
    Function Name: interpretBestMove
    Purpose: This function will interpret the computers move, and create a string that explains why it was chosen.
    Parameters:
               bestTiles, vector of tiles passed in by reference. stores the computer chosen tiles 
               trains, vector of characters passed in by reference, stores the corresponding trains for the tiles chosen
    Return Value: string that represents the reasoning for the computers choice of tiles to play
    Algorithm:
                1-If the tile is a double, we played it since it was the largest double.
                2-If the tile is not a double, then it was either the largest non-double or the largest follow up tile.
    Assistance Received: None.
    ********************************************************************* */
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
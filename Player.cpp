#include "Player.h"

/* *********************************************************************
Function Name: Player
Purpose: Set default values of Player member variables.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
Player::Player()
{
    this->playerTrain = {};
    this->playerHand = {};
    this->trainLastNumber = -1;
    //these 3 booleans dictate weather the player can play on each train.
    this->humanTrainPlayable = false;
    this->computerTrainPlayable = false;
    this->mexicanTrainPlayable = false;
}

/* *********************************************************************
Function Name: addTileToHand
Purpose: Add a tile to a players hand. used when they pick a card from a boneyard
Parameters:
    Tile tileToAdd - The tile that the user picked from the boneyard and needs to add into their hand
Return Value: None
Assistance Received: None.
********************************************************************* */
void Player::addTileToHand(Tile tileToAdd)
{
    playerHand.addTile(tileToAdd);
}

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
void Player::removeTileFromHand(int value1, int value2)
{
    playerHand.removeTile(value1, value2);
}

/* *********************************************************************
Function Name: : getTrainMarker
Purpose: check if a player train has a marker on it.
Parameters: None
Return Value: True if there is a maker, false otherwise.
Assistance Received: None.
********************************************************************* */
bool const Player::getTrainMarker()
{
    return playerTrain.getMarker();
}

/* *********************************************************************
Function Name: : setTrainMarker
Purpose: Set a players train marker to true
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */

void Player::setTrainMarker()
{
    playerTrain.setMarker();
}

/* *********************************************************************
Function Name: : resetTrainMarker
Purpose: Set a players train marker to false
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
void Player::resetTrainMarker()
{
    this->playerTrain.clearMarker();
}

/* *********************************************************************
Function Name: : getOrphanDouble
Purpose: Checks a players train and looks for an orphan double.
Parameters: None
Return Value: true ifthe players train has an orphan double, false if it doesnt.
Assistance Received: None.
********************************************************************* */

bool const Player::getOrphanDouble()
{
    return this->playerTrain.getOrphanDouble();
}
/* *********************************************************************
Function Name: : setOrphanDouble
Purpose: set a player trains orphan double boolean to true.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */

void Player::setOrphanDouble()
{
    playerTrain.setOrphanDouble();
}


/* *********************************************************************
Function Name: : resetOrphanDouble
Purpose: Reset a player trains orphan double, setting it back to false. used after they plan on the orphan double
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
void Player::resetOrphanDouble()
{
    playerTrain.resetOrphanDouble();
}

/* *********************************************************************
Function Name: : setTrainEndNumber
Purpose: Set a trains end number to the new value passed to the function.
         The trains end number is the number that is left "hanging" that new tiles have to match.
Parameters: newEndNumber, integer that is the new train's end number.
Return Value: None
Assistance Received: None.
*********************************************************************  */
void Player::setTrainEndNumber( int newEndNumber)
{
    playerTrain.setTrainEndNumber(newEndNumber);
}

/* *********************************************************************
Function Name: : getTrainEndNumber
Purpose: get the end number of a train that tiles must match in order to be added to that train
Parameters: None
Return Value: integer value that represents the last number on the train that must be matched.
Assistance Received: None.
*********************************************************************  */

int const Player::getTrainEndNumber()
{
    return this->playerTrain.getTrainEndNumber();
}

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
bool Player::playerHasMove(int trainEndNumber)
{
    for (int i = 0; i < playerHand.getSize(); i++) {
        if (playerHand[i].getFirstNumber() == trainEndNumber) {
            return true;
        }
        else if (playerHand[i].getSecondNumber() == trainEndNumber) {
            return true;
        }
    }
    return false;
}

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
bool Player::existsValidMove(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain)
{
    //validMove will be set to false, and we will check every train for a valid move.
    //if theres a valid move, we will turn it true.
    bool validMove = false;
    //if the user can play on the human train, and the player has a move on the train, set validMove to true.
    if (this->humanTrainPlayable && playerHasMove(humanPlayer->getTrainEndNumber())) {
        validMove = true;
    } 

    //if the user can play on the computer train, and the player has a move on the train, set validMove to true.
    if (this->computerTrainPlayable && playerHasMove(computerPlayer->getTrainEndNumber())) {
        validMove = true;
    }

    //if the user can play on the mexican train, and the player has a move on the train, set validMove to true.
    if (this->mexicanTrainPlayable && playerHasMove(mexicanTrain.getTrainEndNumber())) {
        validMove = true;
    }
    return validMove;
}

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
bool Player::verifyTileChoice(std::string userInput)
{
    //have to check if string is greater then 3 because of null character ('\0')
    if (userInput.length() > 3) {
        std::cout << "\nError: The tile you entered " << userInput << " is too long to be a valid tile\n";
        return false;
    }
    //check if string is less then or equal to 2 because the null character adds 1 to the size.
    else if (userInput.size() <= 2) {
        std::cout << "\nError: The tile you entered " << userInput << " is too short to be a valid tile\n";
        return false;
    }//if the first or third characters arent digits, then its an invalid tile
    else if (!isdigit(userInput[0]) || !isdigit(userInput[2])) {
        std::cout << "\nError: The tile " << userInput << " Does not have a valid format, one of the characters is not a number\n";
        return false;
    }//if the second character is not a '-', its an invalid tile
    else if (userInput[1] != '-') {
        std::cout << "\nError: The tile you entered " << userInput << " must be seperated by a '-'\n";
        return false;
    }
    //if we pass all the tests, its a valid tile.
    return true;
}

/* *********************************************************************
Function Name: : validateTrainChoice
Purpose: Check if the user entered a valid train,  and if they can actually play on that train.
Parameters: userTrain, Character which the user enters to signal what train they want to play on
Return Value: boolean value. True if the user entered a valid train and can play on it, false if they didnt
Assistance Received: None.
*********************************************************************  */
bool Player::validateTrainChoice(char userTrain)
{
    //train has to be 'h', 'c', or 'm'
    if (userTrain != 'h' && userTrain != 'c' && userTrain != 'm') {
        std::cout << "Error: you entered an invalid train.";
        return false;
    }
    //we check if the user can play on the tile they chose as well.
    else if (userTrain == 'h' && !getHumanTrainPlayable()) {
        std::cout << "Error: You are not allowed to play on the human train."; 
        return false;
    }
    else if (userTrain == 'c' && !getComputerTrainPlayable()) {
        std::cout << "Error: You are not allowed to play on the computer train";
        return false;
    }
    else if (userTrain == 'm' && !getMexicanTrainPlayable()) {
        std::cout << "Error: You are not allowed to play on the Mexican Train";
        return false;
    }
    return true;
}

/* *********************************************************************
Function Name: : getHumanTrainPlayable
Purpose: Check if the player object can play on the human train
Parameters: None
Return Value: True if the player can play on the human train, false if it cant
Assistance Received: None.
*********************************************************************  */
bool const Player::getHumanTrainPlayable()
{
    return this->humanTrainPlayable;
}

/* *********************************************************************
 Function Name: : setHumanTrainPlayable
 Purpose: set the boolean humanTrainPlayable value to true.
 Parameters: None
 Return Value: None
 Assistance Received: None.
 *********************************************************************  */
void Player::setHumanTrainPlayable()
{
    this->humanTrainPlayable = true;
}

/* *********************************************************************
 Function Name: : getComputerTrainPlayable
 Purpose: get the computerTrainPlayable boolean which tells us if the player object can play on that train
 Parameters: None
 Return Value: a boolean value, true if the player can play on the train, false if they cant
 Assistance Received: None.
 *********************************************************************  */
bool const Player::getComputerTrainPlayable()
{
    return this->computerTrainPlayable;
}

/* *********************************************************************
 Function Name: : setComputerTrainPlayable
 Purpose: set the computerTrainPlayable boolean to true, which lets the player play on that train
 Parameters: None
 Return Value: void
 Assistance Received: None.
 *********************************************************************  */
void Player::setComputerTrainPlayable()
{
    this->computerTrainPlayable = true;
}

/* *********************************************************************
 Function Name: : getMexicanTrainPlayable
 Purpose: get the mexicanTrainPlayable boolean, which lets us know if we can play on the mexican train
 Parameters: None
 Return Value: bool, true if we are allowed to play on the mexican train
 Assistance Received: None.
 *********************************************************************  */
bool const Player::getMexicanTrainPlayable()
{
    return this->mexicanTrainPlayable;
}

/* *********************************************************************
 Function Name: : getHandSize
 Purpose: Check the size of a players hand
 Parameters: None
 Return Value: the size of the players hand, an integer
 Assistance Received: None.
 *********************************************************************  */
int const Player::getHandSize()
{
    return this->playerHand.getSize();
}

/* *********************************************************************
 Function Name: : getHand
 Purpose: get the players hand
 Parameters: None
 Return Value: const vector<Tile>, which is the vector of all the tiles on a train
 Assistance Received: None.
 *********************************************************************  */
const std::vector<Tile> Player::getHand()
{
    return this->playerHand.getHand();
}

/* *********************************************************************
 Function Name: : getTrain
 Purpose: get the players train
 Parameters: None
 Return Value: const deque<Tile>, which is the deque of all the tiles on a train
 Assistance Received: None.
 *********************************************************************  */

const std::deque<Tile> Player::getTrain()
{
    return this->playerTrain.getTrainDeque();
}

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
std::vector<Tile> Player::getPlayableTiles(std::vector<Tile> playerHand, int trainEndNumber)
{
    std::vector<Tile> playableTiles;
    //1)Loop through playerHand
    for (int i = 0; i < playerHand.size(); i++) {
        //2)if the tile's first number is equal to the trains end number, add the tile to vector we return

        if (playerHand[i].getFirstNumber() == trainEndNumber) {
            playableTiles.push_back(Tile(playerHand[i].getFirstNumber(), playerHand[i].getSecondNumber()));
        }
        //3)else if the tile's second number is equal to the trains end number, add the tile to vector we return
        else if (playerHand[i].getSecondNumber() == trainEndNumber) {
            playableTiles.push_back(Tile(playerHand[i].getFirstNumber(), playerHand[i].getSecondNumber()));
        }
    }
    return playableTiles;
}    

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
bool Player::checkOrphanDoubles(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain)
{
    bool orphanDouble = false;
    //1- check if there exists any orphan double on a train
    if (humanPlayer->getOrphanDouble() == true || computerPlayer->getOrphanDouble() == true || mexicanTrain.getOrphanDouble() == true) {
        //make all trains unplayable. later we will check which trains have orphan doubles and set them as the only trains playable
        this->humanTrainPlayable = false;
        this->computerTrainPlayable = false;
        this->mexicanTrainPlayable = false;
    }
    //check if each train has an orphan double. if it does, make that train playable, and set orphanDouble to true.
    if (humanPlayer->getOrphanDouble() == true) {
        std::cout << "\nThere is an orphan double on the human train.\n";
        this->humanTrainPlayable = true;
        orphanDouble = true;
    }
    if (computerPlayer->getOrphanDouble() == true) {
        std::cout << "\nThere is an orphan double on the computer train.\n";
        this->computerTrainPlayable = true;
        orphanDouble = true;
    }
    if (mexicanTrain.getOrphanDouble() == true) {
        std::cout << "\nThere is an orphan double on the mexican train.\n";
        this->mexicanTrainPlayable = true;
        orphanDouble = true;
    }
    return orphanDouble;
}

/* *********************************************************************
 Function Name: : hasTile
 Purpose: Check to make sure a player has a tile that they entered
 Parameters: userInputAsTile, Tile object passed by value that is used to check if the player has that tile.
 Return Value: Boolean value, true if a player has the tile in their hand
 Assistance Received: None.
 *********************************************************************  */
bool Player::hasTile(Tile userInputAsTile)
{
    //loop through players hand
    //every index check if the first and second number matches userInputAsTile, which is the tile we are checking is in the hand.
    for (int i = 0; i < playerHand.getSize(); i++) {
        if (playerHand[i].getFirstNumber() == userInputAsTile.getFirstNumber() && playerHand[i].getSecondNumber() == userInputAsTile.getSecondNumber()) {
            return true;
        }
    }
    return false;
}

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
            6)if they dont have a valid move, set a marker on their train and return false
            7)else, return true.
 Assistance Received: None.
 *********************************************************************  */
bool Player::noPlayableTiles(Player * humanPlayer, Player * computerPlayer, Train & mexicanTrain, Hand & boneyard)
{
    //1)check if the boneyard is empty
    if (boneyard.getSize() == 0) {
        // 1a) if it is, output that its empty, add a marker to player train, return false
        std::cout << "Boneyard is empty, a marker is placed on your train";
        this->setTrainMarker();
        return false;
    }
    else {
        //2) else, get the top tile of the boneyard.
        Tile boneyardTile = boneyard.getTile(0);
        //3) remove that tile from the boneyard
        boneyard.removeTile(0);
        //4)add the tile to players hand.
        this->addTileToHand(boneyardTile);
        //5)check if the user has a valid move after adding the boneyard tile to their hand

        bool validMove = this->existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
        if (!validMove) {
            //6)if they dont have a valid move, set a marker on their train and return false
            std::cout << "You have no valid moves after taking the tile ";
            boneyardTile.printTile();
            std::cout << " from the boneyard.\nA marker has been place on your train.";
            this->setTrainMarker();
            //drawn tile is not playable. return false
            return false;
        }
        else {
            //7)else, return true.
            std::cout << "The tile drawn from the boneyard, ";
            boneyardTile.printTile();
            std::cout << " is playable. restarting turn.";
            //drawn tile is playable, return true.
            return true;
        }
    }
}

/* *********************************************************************
 Function Name: : sumOfPips
 Purpose: returns the sum of pips that a player has left in their hands
 Parameters: None
 Return Value: integer value that is the sum of the pips left
 Assistance Received: None.
 ********************************************************************  */
int Player::sumOfPips()
{
    //total will hold the sum of the pips in the hand
    int total = 0;
    //for every tile in the players hand, add the first and second number to total.
    for (int i = 0; i < playerHand.getSize(); i++) {
        total += playerHand[i].getFirstNumber();
        total += playerHand[i].getSecondNumber();
    }
    return total;
}

/* *********************************************************************
 Function Name: : clearData
 Purpose: clears the data player hand and player train data to get it ready for next round
 Parameters: None
 Return Value: None
 Assistance Received: None.
 *********************************************************************  */
void Player::clearData()
{
    this->playerTrain.clearTrain();
    this->playerHand.clearHand();
}

/* *********************************************************************
 Function Name: : playerTileChoice
 Purpose: ask user for a tile, and verify that it is valid
 Parameters: None
 Return Value: Tile, which is a tile object that is based on what the user entered.
 Assistance Received: None.
 *********************************************************************  */
Tile Player::playerTileChoice()
{
    std::string userInput;
    std::cout << "\nChoose a tile in x-y format to play (ie - 0-0)";
    std::cin >> userInput;
    //verify that the user entered a valid form for a tile
    if (!verifyTileChoice(userInput)) {
        return Tile(-1, -1);
    }

    Tile userInputAsTile = Tile(userInput[0] - 48, userInput[2] - 48);
    //make sure user has tile
    if (!hasTile(userInputAsTile)) {
        std::cout << "\n\nError: you do not have that tile. Restarting Move. \n\n\n\n\n";
        return Tile(-1, -1);
    }

    return Tile(userInput[0] - 48, userInput[2] - 48);
}

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
void Player::findBestMove(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, std::vector<Tile>& bestTiles, std::vector<char>& trains)
{
    std::string bestMoveExplination = "";
    bool turnFinished = false;
    //stores what tiles the computer will play. either 1 single tile, a double and a non doubl, or 2 doubles and a non double.
    std::vector<Tile> tilesPlayed;
    std::vector<Tile> mexicanPlayableTiles;
    std::vector<Tile> humanPlayableTiles;
    std::vector<Tile> computerPlayableTiles;

    //stores any double tiles the player can play
    std::vector<Tile> mexicanDoubles;
    std::vector<Tile> humanDoubles;
    std::vector<Tile> computerDoubles;
    //create a temporary hand that we can change and see what moves are available without changing the players actual hand until we need too.
    std::vector<Tile> tmpVector = this->getHand();
    Hand tempPlayerHand;
    for (int i = 0; i < tmpVector.size(); i++) {
        tempPlayerHand.addTile(tmpVector[i]);
    }
    //need to keep track of doubles played so we dont play 3 or more.
    int doublesPlayed = 0;
    
    
    do {
        //clear all vectors of playable tiles.
        mexicanPlayableTiles.clear();
        humanPlayableTiles.clear();
        computerPlayableTiles.clear();
        mexicanDoubles.clear();
        humanDoubles.clear();
        computerDoubles.clear();

        //3a- if mexican train is playable, get all the playable tiles on that train and place them into mexicanPlayableTiles vector
        if (this->getMexicanTrainPlayable()) {
            mexicanPlayableTiles = getPlayableTiles(tempPlayerHand.getHand(), mexicanTrain.getTrainEndNumber());
        }
        //3b- if computer train is playable, get all the playable tiles on that train and place them into computerPlayableTiles vector

        if (this->getComputerTrainPlayable()) {
            computerPlayableTiles = getPlayableTiles(tempPlayerHand.getHand(), computerPlayer->getTrainEndNumber());
        }
        //3c- if human train is playable, get all the playable tiles on that train and place them into humanPlayableTiles vector

        if (this->getHumanTrainPlayable()) {
            humanPlayableTiles = getPlayableTiles(tempPlayerHand.getHand(), humanPlayer->getTrainEndNumber());
        }

        //3d- store all the doubles into their respective doubles vector
        for (int i = 0; i < mexicanPlayableTiles.size(); i++) {
            if (mexicanPlayableTiles[i].isDouble()) {
                mexicanDoubles.push_back(mexicanPlayableTiles[i]);
            }
        }

        for (int i = 0; i < humanPlayableTiles.size(); i++) {
            if (humanPlayableTiles[i].isDouble()) {
                humanDoubles.push_back(humanPlayableTiles[i]);
            }
        }

        for (int i = 0; i < computerPlayableTiles.size(); i++) {
            if (computerPlayableTiles[i].isDouble()) {
                computerDoubles.push_back(computerPlayableTiles[i]);
            }
        }

        //3e - If we can play on the mexican train, and the mexicanDoubles vector isnt empty, and we have played less then 2 doubles,
        //add the first double to bestTiles vector.remove the tile from out temporary hand, and restart from step 3.
        if (getMexicanTrainPlayable() & !mexicanDoubles.empty() && doublesPlayed < 2) {
            tilesPlayed.push_back(mexicanDoubles[0]);
            if (mexicanDoubles[0].getFirstNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(mexicanDoubles[0].getSecondNumber());
            }
            else if (mexicanDoubles[0].getSecondNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(mexicanDoubles[0].getFirstNumber());
                mexicanDoubles[0].swapNumbers();
            }
            //remove the tile from the temp hand, and add the tile and train to the respective vectors
            tempPlayerHand.removeTile(mexicanDoubles[0].getFirstNumber(), mexicanDoubles[0].getSecondNumber());
            bestTiles.push_back(mexicanDoubles[0]);
            trains.push_back('m');
            //increment doubles played.
            doublesPlayed++;
            continue;
        } 
        //3f- If we can play on the human train, and the mexicanDoubles vector isnt empty, and we have played less then 2 doubles,
        // add the first double to bestTiles vector.remove the tile from out temporary hand, and restart from step 3.
        else if (getHumanTrainPlayable() && !humanDoubles.empty() && doublesPlayed < 2) {
            tempPlayerHand.removeTile(humanDoubles[0].getFirstNumber(), humanDoubles[0].getSecondNumber());
            bestTiles.push_back(humanDoubles[0]);
            trains.push_back('h');
            doublesPlayed++;
            continue;
        }        
        //3g - If we can play on the computer train, and the mexicanDoubles vector isnt empty, and we have played less then 2 doubles,
        //add the first double to bestTiles vector.remove the tile from out temporary hand, and restart from step 3.
        else if (getComputerTrainPlayable() && !computerDoubles.empty() && doublesPlayed < 2) {
            //remove the tile from the temp hand, and add the tile and train to the respective vectors
            tempPlayerHand.removeTile(computerDoubles[0].getFirstNumber(), computerDoubles[0].getSecondNumber());
            bestTiles.push_back(computerDoubles[0]);
            trains.push_back('c');
            doublesPlayed++;
            continue;

        }
        

        //3h- Repeat steps 3e -3g, except this time for the vector that stores the non double tiles.
        //if we play a single tile, our turn is over so return.
        //push back the correct tile to the bestTiles vector 
        //and push back the correct character to the trains vector.
        if (getMexicanTrainPlayable() && !mexicanPlayableTiles.empty()) {
            bestTiles.push_back(mexicanPlayableTiles[0]);          
            tempPlayerHand.removeTile(mexicanPlayableTiles[0].getFirstNumber(), mexicanPlayableTiles[0].getSecondNumber());
            trains.push_back('m');
            return;
        }
        if (getHumanTrainPlayable() && !humanPlayableTiles.empty()) {
            bestTiles.push_back(humanPlayableTiles[0]);
            trains.push_back('h');
            return;
        }
        if (getComputerTrainPlayable() && !computerPlayableTiles.empty()) {
            bestTiles.push_back(computerPlayableTiles[0]);
            trains.push_back('c');
            return;
        }
        return;
    } while (turnFinished == false); 
    
}


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
void Player::printGameState(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engineInt)
{
    std::cout << "=================================================================\n";
    std::cout << "\n\t         Round: " << roundNumber;
    std::cout << "\nHuman Score: " << humanScore;
    std::cout << "\t\t\tComputer Score: " << computerScore;
    std::cout << "\nTrains: \n";
    if (computerPlayer->getTrainMarker()) {
        std::cout << "M ";
    }
    computerPlayer->printTrain();
    std::cout << " " << engineInt << " - " << engineInt << " ,";
    humanPlayer->printTrain();
    if (humanPlayer->getTrainMarker()) {
        std::cout << " M";
    }
    std::cout << "\nMexican Train: ";
    mexicanTrain.printTrain();
    std::cout << "\n\nHuman players hand: \n";
    humanPlayer->printHand();
    std::cout << "\n\nComputer Players Hand: \n";
    computerPlayer->printHand();
    std::cout << "\nNext boneyard tile: ";
    if (boneyard.getSize() != 0) {
        boneyard.getTile(0).printTile();
    }
    else {
        std::cout << "Empty";
    }
    std::cout << "\n\n";

}

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
std::string Player::interpretBestMove(std::vector<Tile>& bestTiles, std::vector<char>& trains)
{
    std::string explination;
    //print out the doubles we played, and the reasoning we played it was because it is a double tile.
    for (int i = 0; i < bestTiles.size(); i++) {
        if (bestTiles[i].isDouble()) {
            explination += std::to_string(bestTiles[i].getFirstNumber()) + " - " + std::to_string(bestTiles[i].getSecondNumber());
            explination += " was played on the ";
            if (trains[i] == 'm') {
                explination += "mexican";
            }
            else if (trains[i] == 'c') {
                explination += "computer";
            }
            else {
                explination += "human";
            }
            explination += " train because it was a valid double tile.";
        }
    }
    
    //need to make sure we print out the last tile that is not a double.
    if (!bestTiles.back().isDouble()) {
        explination += std::to_string(bestTiles.back().getFirstNumber()) + " - " + std::to_string(bestTiles.back().getSecondNumber());
        explination += " was played on the ";
        if (trains.back() == 'm') {
            explination += "mexican";
        }
        else if (trains.back() == 'c') {
            explination += "computer";
        }
        else {
            explination += "human";
        }

        explination += " train because it was the largest tile.\n\n";
    }
    return explination;
}

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
bool Player::tileFitsOnTrain(Tile tileToCheck, int trainEndNumber)
{
    if (tileToCheck.getFirstNumber() == trainEndNumber) {
        return true;
    }
    else if (tileToCheck.getSecondNumber() == trainEndNumber) {
        return true;
    }
    std::cout << "Error: The tile you selected does not fit on the train\n";
    return false;
}

/* *********************************************************************
Function Name: printTrain
Purpose: print a train to the console.
Parameters:None
Return Value: None
Assistance Received: None.
********************************************************************* */
void Player::printTrain()
{
    playerTrain.printTrain();
}

/* *********************************************************************
Function Name: printHand
Purpose: print a players hand to the console.
Parameters:None
Return Value: None
Assistance Received: None.
********************************************************************* */
void Player::printHand() {
    playerHand.printHand();
}
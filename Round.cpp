#pragma once
#include "Round.h"

/* *********************************************************************
Function Name: Round
Purpose: Set default values of Round member variables.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
Round::Round()
{
    this->humanPlayer = new Human;
    this->computerPlayer = new Computer;

    this->m_boneyard = {};
    this->engineQueue = {};
    this->mexicanTrain = {};
    this->engineInt = -1;
    //these 3 booleans will dictate whether a player can place a tile on a train.
    this->humanTurn = false;
    this->computerTurn = false;
    this->computerWon = false;
    this->humanWon = false;
}

/* *********************************************************************
Function Name: getHands
Purpose: retrive a players hand as a vector. Needed to save the game
Parameters: whoseHand, integer value thats passed in so we can check whose hand we need.
                0 is computer, 1 is human, 2 is mexican.
Return value: vector of Tiles that is a copy of the players hand.
Assistance Received: None.
********************************************************************* */
const std::vector<Tile> Round::getHands(int whoseHand)
{

    if (whoseHand == 0) {
        //computer hand        
        return this->computerPlayer->getHand();
    }
    else if (whoseHand == 1) {
        //human hand
        return this->humanPlayer->getHand();
    }
    else {
        //boneyard
        return this->m_boneyard.getHand();
    }
}

/* *********************************************************************
Function Name: getTrains
Purpose: retrive a players train as a deque. Needed to save the game
Parameters: whoseHand, integer value thats passed in so we can check whose hand we need.
                0 is computer, 1 is human, 2 is mexican.
Return value: vector of Tiles that is a copy of the players train.
Assistance Received: None.
********************************************************************* */
const std::deque<Tile> Round::getTrains(int whoseTrains)
{
    if (whoseTrains == 0) {
        //computer hand        

        return this->computerPlayer->getTrain();
    }
    else if (whoseTrains == 1) {
        //human hand
        return this->humanPlayer->getTrain();
    }
    else {
        //mexican train
        return this->mexicanTrain.getTrainDeque();
    }
}

/* *********************************************************************
Function Name: getEngineInt
Purpose: retrive the value of the engine
Parameters: None
Return value: integer value that is the value of the current rounds engine tile
Assistance Received: None.
********************************************************************* */
int Round::getEngineInt()
{
    return this->engineInt;
}

/* *********************************************************************
Function Name: getHumanTurn
Purpose: check if its currently the humans turn. if it is not, then its the computers turn
Parameters: None
Return value: bool, true if it is the computers turn , false if it is not
Assistance Received: None.
********************************************************************* */
bool Round::getHumanTurn()
{
    return this->humanTurn;
}

/* *********************************************************************
Function Name: getHumanTrainMarker
Purpose: check if the human players train has a marker
Parameters: None
Return value: Bool, true if the human train has a marker on it, false if it doesnt
Assistance Received: None.
********************************************************************* */
bool Round::getHumanTrainMarker()
{
    return this->humanPlayer->getTrainMarker();
}

/* *********************************************************************
Function Name: getComputerTrainMarker
Purpose: check if the cpu's train has a marker
Parameters: None
Return value: Bool, true if the cpu train has a marker on it, false if it doesnt
Assistance Received: None.
********************************************************************* */
bool Round::getComputerTrainMarker()
{
    return this->computerPlayer->getTrainMarker();
}

/* *********************************************************************
Function Name: getWinner
Purpose: gets the winner of a round
Parameters: None
Return value: bool, true if the human won, false if the computer won
Assistance Received: None.
********************************************************************* */
bool Round::getWinner()
{
    if (humanWon) {
        return true;
    }
    return false;//computer won.
}

/* *********************************************************************
Function Name: getNextEngineValue
Purpose: Get the integer for the next engine value
Parameters: None
Return value: integer that is the next engine value
Assistance Received: None.
********************************************************************* */
int Round::getNextEngineValue() {
    if (engineQueue.empty()) {
        resetEngineQueue();
    }
    int tmpVal = engineQueue.front();
    engineInt = tmpVal;
    engineQueue.pop_front();
    return tmpVal;
}

/* *********************************************************************
Function Name: setHumanTurn
Purpose: set the humans turn to true, and compuers turn to false
Parameters: None
Return value: None
Assistance Received: None.
********************************************************************* */
void Round::setHumanTurn()
{
    this->humanTurn = true;
    this->computerTurn = false;
}

/* *********************************************************************
Function Name: setComputerTurn
Purpose: set the computers turn to true, and the humans to false
Parameters: None
Return value: None
Assistance Received: None.
********************************************************************* */
void Round::setComputerTurn()
{
    this->computerTurn = true;
    this->humanTurn = false;
}

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
int Round::startRound(bool serialiedStart, int humanScore, int computerScore, int roundNumber)
{
    //step 1- check if we are starting the game from a fle we already loaded.
    //if we are, then we do not have to instantiate deck or remove engine tile, shuffle the deck etc. we can just start
    //if we are NOT loading the game from a file, we must setup the game properly.
    //instantiate deck by creating all tiles. remove the current engine tile, and shuffle the deck and deal the tiles to player and comptuer.
    if(!serialiedStart){
        instantiateDeck();
        //remove the engine tile from the deck
        removeEngineTile();
        shuffleDeck();
        dealTiles();
        //set the train end numbers to the correct engine value.
        setTrainEndNumbers();
        whoGoesFirst(humanScore, computerScore);
    }
    int pipsValue = startTurn(humanScore, computerScore, roundNumber);
    //game is over, remove all lingering data incase user wants to play another round.
    //HOWEVER if we want to save the game, then we dont want to clean the data. we want to keep it
    //so we check if the pipsValue returned is -10, which is our value for a user choosing to save the game
    if (pipsValue != -10) {
        cleanData();
    }

    return pipsValue;
}

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
void Round::whoGoesFirst(int humanScore, int computerScore)
{
    if (humanScore < computerScore) {
        std::cout << "The human has a lower score, so you get to go first. \n";
        setHumanTurn();
        return;
    }
    else if (computerScore < humanScore) {
        std::cout << "The computer has a lower score, so the computer goes first.\n";
        setComputerTurn();
        return;
    }
    //coin flip: 
    std::string userChoice;
    do {
        std::cout << "\n\nBoth players have the same score.\nA coint toss will determine who goes first.\n";
        std::cout << "Enter 1 for heads, 2 for tails: ";
        std::cin >> userChoice;
        //verify  user input
        if (userChoice != "1" && userChoice != "2") {
            std::cout << "Error: invalid value entered. Try again.\n";
        }
    } while (userChoice != "1" && userChoice != "2");

    int randomNum = (rand() % 2) + 1;
    if (std::to_string(randomNum) == userChoice) {
        std::cout << "\nCongratulations! you guessed correctly and you have the first turn.\n\n";
        setHumanTurn();
    }
    else {
        std::cout << "\nSorry, you guessed wrong and the computer goes first.\n\n";
        setComputerTurn();
    }
}

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
void Round::instantiateDeck() {
    //create and add an entire double 9 set to the boneyard
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            m_boneyard.addTile(Tile(i, j));
        }
    }
}

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
void Round::shuffleDeck() {
    srand(time(0));
    //for every tile, pick a random index from 0 to the amount of tiles, and switch those 2 tiles.
    for (int i = 0; i < m_boneyard.getSize(); i++) {
        int randomNum = rand() % m_boneyard.getSize();
        Tile tmpTile = m_boneyard.getTile(i);
        m_boneyard[i] = m_boneyard.getTile(randomNum);
        m_boneyard[randomNum] = tmpTile;
    }
}

/* *********************************************************************
Function Name: dealTiles
Purpose: deal the tiles to the players.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
void Round::dealTiles() {
    for (int i = 0; i < 16; i++) {
        humanPlayer->addTileToHand(m_boneyard[i]);
    }
    for (int i = 16; i < 32; i++) {
        computerPlayer->addTileToHand(m_boneyard[i]);
    }
    for (int i = 31; i >= 0; i--) {
        m_boneyard.removeTile(i);
    }
}

/* *********************************************************************
Function Name: removeEngineTile
Purpose: remove the tile that will be the engine for the round from the deck
Parameters: None
Return value: None
Assistance Received: None.
********************************************************************* */
void Round::removeEngineTile()
{
    int engineValue = getNextEngineValue();
    m_boneyard.removeTile(engineValue, engineValue);
}

/* *********************************************************************
Function Name: setTrainEndNumbers
Purpose: Initialize the train's end numbers to be the engine int.
Parameters: None
Return value: None
Assistance Received: None.
********************************************************************* */
void Round::setTrainEndNumbers()
{
    humanPlayer->setTrainEndNumber(engineInt);
    computerPlayer->setTrainEndNumber(engineInt);
    mexicanTrain.setTrainEndNumber(engineInt);
}

/* *********************************************************************
Function Name: resetEngineQueue
Purpose: reset the queue that stores the engine values so that the queue will hold 9-0 in descending order.
Parameters: None
Return value: None
Assistance Received: None.
********************************************************************* */
void Round::resetEngineQueue() {
    engineQueue.clear();
    for (int i = 0; i < 10; i++) {
        engineQueue.push_front(i);
    }
}


/* *********************************************************************
Function Name: setEngineValue
Purpose: set the engine value to a certain integer we pass in. This is used in serialization to begin with the proper engine
Parameters: engineVal, integer that is the number we want our engine to be.
Return value: None
Assistance Received: None.
********************************************************************* */
void Round::setEngineValue(int engineVal)
{
    //set the engine value to a number we pass in, and pop values off the engine queue until we reach that number
    if (engineQueue.empty()) {
        resetEngineQueue();
    }
    while (this->engineInt != engineVal) {
        engineInt = getNextEngineValue();
    }
}

/* *********************************************************************
Function Name: startTurn
Purpose: Start both computer and players turn until the round is over.
Parameters: humanScore- integer value that stores the human players score. Passed so we can print it out before every turn
            computerScore- integer value that stores the computer players score. Passed so we can print it out before every turn
            roundNumber - integer value that stores the current round number. passed so we can print it before every turn
Return value: Integer value
Assistance Received: None.
********************************************************************* */
int Round::startTurn(int humanScore, int computerScore, int roundNumber)
{   
    //integers that will store the sum of pips of the tiles in a players hand when the other player empties their hand
    int humanPipsLeft = 0;
    int computerPipsLeft = 0;

    
    do {
        
        if (humanTurn) {
            char userChoice = outputMenu(true);
            //if the user wants to save the game, return -10
            if (userChoice == 's') {
                return -10; //-10 is the code to save game
            }
            std::cout << "\n\n\n";
            std::cout << "=================================================================\n";
            std::cout << "=======================Human Players Turn========================\n";
            std::cout << "=================================================================\n";
            //start the human players turn. If the human's hand is empty and they win the game, the value returned will be the computer player's pips left in their hand
            computerPipsLeft = humanPlayer->play(this->humanPlayer, this->computerPlayer, this->mexicanTrain, this->m_boneyard, humanScore, computerScore, roundNumber, this->getEngineInt());
            setComputerTurn();
        }

        //if humanPlayer->play returns a positive integer, then that is the sum of pips left in the computers hand.
        if (computerPipsLeft > 0) {
            humanWon = true;
            return computerPipsLeft;
        }
        
        //COMPUTERS TURN
        if (computerTurn) {
            char userChoice =outputMenu(false);
            //if the user wants to save the game, return -10
            if (userChoice == 's') {
                return -10; //-10 is the code to save game
            }
            std::cout << "\n\n\n";
            std::cout << "=================================================================\n";
            std::cout << "=====================Computer Players Turn=======================\n";
            std::cout << "=================================================================\n";
            humanPipsLeft = computerPlayer->play(this->humanPlayer, this->computerPlayer, this->mexicanTrain, this->m_boneyard, humanScore, computerScore, roundNumber, this->getEngineInt());
            setHumanTurn();
        }

        //-666 is  our error code for the boneyard being empty and players skipping their turn
        //if  both players have to go to the boneyard, and they dont have a valid move, the game locks up.
        if (humanPipsLeft == -666 && computerPipsLeft == -666) {
            std::cout << "\n\nBoth players had to skip their turn, and the boneyard is empty. Restarting round.\n";
            return 0;
        }

        //if computerPlayer->play returned a positive value, then that is the sum of pips left in the human players hand while the cpu players was empty.
        //return that value.
        if (humanPipsLeft > 0) {
            computerWon = true;
            return humanPipsLeft;
        }

    } while (true);
}

/* *********************************************************************
Function Name: drawFromBoneyard
Purpose: take the top tile from the boneyard, and return it
Parameters: None
Return value: Tile object that represents the top tile of the boneyard
Assistance Received: None.
********************************************************************* */
Tile Round::drawFromBoneyard()
{
    //if the boneyard is empty, return and invalid tile (-1--1) so that we can check it and know.
    if (m_boneyard.getSize() == 0) {
        return Tile(-1, -1);
    }
    Tile tmpTile = m_boneyard.getTile(0);
    m_boneyard.removeTile(0);
    return tmpTile;
}

/* *********************************************************************
Function Name: setTrainMarker
Purpose: set a player trains marker
Parameters: whoseTrain, integer value that represents whose train we turn the marker on for.
            0 is computer, 1 is human, 2 is mexican.
Return value: void
Assistance Received: None.
********************************************************************* */
void Round::setTrainMarker(int whoseTrain)
{
    if (whoseTrain == 0) {
        //computer train
        this->computerPlayer->setTrainMarker();
    }
    else if (whoseTrain == 1) {
        //human train
        this->humanPlayer->setTrainMarker();
    }
    else if (whoseTrain == 2) {
        //mehicano train
        mexicanTrain.setMarker();
    }
}

/* *********************************************************************
Function Name: cleanData
Purpose: clean all the round data so we can play a new round with no lingering tiles
Parameters: None
Return value: none
Assistance Received: None.
********************************************************************* */
void Round::cleanData()
{
    //clear boneyard, player hand, computer hand.
    this->computerPlayer->clearData();
    this->humanPlayer->clearData();
    this->m_boneyard.clearHand();
    this->mexicanTrain.clearTrain();
    //clear orphan doubes
    computerPlayer->resetOrphanDouble();
    humanPlayer->resetOrphanDouble();
    mexicanTrain.resetOrphanDouble();
}

/* *********************************************************************
Function Name: setHand
Purpose: set a players hand to equal a deque of tiles, used in seralization
Parameters: tiles, deque of tiles passed in by value that we will loop through and add all values to a players hand
            whoseHand, integer value that represents whose hand we fill
            0 is computer, 1 is human, 2 is mexican.
Return value: void
Assistance Received: None.
********************************************************************* */
void Round::setHand(std::deque<Tile> tiles, int whoseHand)
{
    //for every tile in Tiles, add the tile at i to the corresponding hand
    for (int i = 0; i < tiles.size(); i++) {
        if (whoseHand == 0) {
            //add to computer hand
            computerPlayer->addTileToHand(tiles[i]);
        }
        else if (whoseHand == 1) {
             //add to human hand        
            humanPlayer->addTileToHand(tiles[i]);
        }
        else if (whoseHand == 2) {
            //add to boneyard.
            m_boneyard.addTile(tiles[i]);
        }
    }
}

/* *********************************************************************
Function Name: setTrain
Purpose: set a players train to equal a deque of tiles, and set their end numbers to the corresponding value. used in seralization
Parameters: tiles, deque of tiles passed in by value that we will loop through and add all values to a players train
            whoseHand, integer value that represents whose train we fill
            0 is computer, 1 is human, 2 is mexican.
Return value: void
Assistance Received: None.
********************************************************************* */
void Round::setTrain(std::deque<Tile> tiles, int whoseTrain)
{
    //if deque of tiles is empty, then we dont need to add anything so just return
    if (tiles.empty()) {
        return;
    }
    for (int i = 0; i < tiles.size(); i++) {
        //set train values
        if (whoseTrain == 0) {
            //add to computer hand
            computerPlayer->addTileToTrain(tiles[i]);
        }
        else if (whoseTrain == 1) {
            //add to human hand        
            humanPlayer->addTileToTrain(tiles[i]); 
        }
        else if (whoseTrain == 2) {
            //add to boneyard.
            mexicanTrain.addTileBack(tiles[i]);
        }
    }
    //set train end numbers.
    //also check front of computer train/back of human train and mexican train for orphan doubles.
    if (whoseTrain == 0) {
        //set computer train end number
        computerPlayer->setTrainEndNumber(tiles.at(tiles.size() - 1).getFirstNumber());
        if (tiles[tiles.size() - 1].isDouble()) {
            //set orphan double
            computerPlayer->setOrphanDouble();
        }
    }
    else if (whoseTrain == 1) {
        //set human train end number        
        humanPlayer->setTrainEndNumber(tiles.at(tiles.size() - 1).getSecondNumber());
        if (tiles[tiles.size() - 1].isDouble()) {
            //set orphan double
            humanPlayer->setOrphanDouble();
        }
    }
    else if (whoseTrain == 2) {
        //set mexican train end number
        mexicanTrain.setTrainEndNumber(tiles.at(tiles.size() - 1).getSecondNumber());        
        if (tiles[tiles.size() - 1].isDouble()) {
            //set orphan double
            mexicanTrain.setOrphanDouble();
        }
    }
}

/* *********************************************************************
Function Name: outputMenu
Purpose: Output the menu for the player to choose to save the game, make a move, ask for help, or quit
Parameters: computerTurn, boolean value thats passed in because we dont have the computer ask for help
Return value: char, which is a character that corresponds to what the user chose.
Assistance Received: None.
********************************************************************* */
char Round::outputMenu(bool humanTurn)
{
    char userInput; 
    do {
        //do while loop until the player enters a valid response
        std::cout << "\nSave the game (S/s)\n";
        std::cout << "Make a move (M/m)\n";
        //only ask the human player for help, not the computer player.
        if (humanTurn) {
            std::cout << "Ask for help (H/h)\n";
        }
        std::cout << "Quit the game (Q/q)\n\n";
    
        std::cin >> userInput;
        userInput = tolower(userInput);
        if (userInput != 's' &&  userInput != 'm' && userInput != 'h' && userInput != 'q') {
            std::cout << "\n\nInvalid input. Try again. \n\n\n";
        }
    } while (userInput != 's' &&  userInput != 'm' && userInput != 'h' && userInput != 'q');


    if (userInput == 's') {
        return 's';
    }
    else if (userInput == 'm') {
        return 'h';
    }
    else if (userInput == 'h') {
        //if the human player asks for help: 
        //since we havent started playing, we have to check for orphan doubles/playable trains here.
        if (humanPlayer->checkOrphanDoubles(this->humanPlayer, this->computerPlayer, mexicanTrain) == false) {
            if (this->getComputerTrainMarker()) {
                humanPlayer->setComputerTrainPlayable();
            }
            humanPlayer->setHumanTrainPlayable();
        }
        //create vectors to store the best tiles to play on, and the trains to play on.
        std::vector<Tile> bestTiles;
        std::vector<char> trainsToPlayOn;
        //find the best moves.
        humanPlayer->findBestMove(humanPlayer,computerPlayer,mexicanTrain,m_boneyard, bestTiles, trainsToPlayOn);
        if (bestTiles.empty()) {
            std::cout << "\nYou have no playable moves.\n";
            return 'a';
        }
        std::string help = "I suggest you play ";
        help += humanPlayer->interpretBestMove(bestTiles, trainsToPlayOn);
        //nterpretBestMove has the words "was played" since it is for when the computer plays, but we remove those words so the sentance makes sense
        std::string wp = " was played";
        std::string::size_type index = help.find(help.find(wp));
        if (index != std::string::npos) {
            help.erase(index, wp.length());
        }
        std::cout << help;
    }
    else if (userInput == 'q') {
        exit(1);
    }


}






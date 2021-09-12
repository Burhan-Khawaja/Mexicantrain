#pragma once
#include "Round.h"


void Round::instantiateDeck() {
    //print out all 1-1 - 9-9 pairs
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            m_boneyard.addTile(Tile(i, j));
        }
    }
}

void Round::shuffleDeck() {
    srand(time(0));
    for (int i = 0; i < m_boneyard.getSize(); i++) {
        int randomNum = rand() % m_boneyard.getSize();
        Tile tmpTile = m_boneyard.getTile(i);
        m_boneyard[i] = m_boneyard.getTile(randomNum);
        m_boneyard[randomNum] = tmpTile;
    }    
}


void Round::dealTiles() {
    //deal 16 cards to computer hand.
    //std::cout << "DEaling tiles to players " << std::endl;

    for (int i = 0; i < 16; i++) {
        humanPlayer.addTileToHand(m_boneyard[i]);
    }    
    for (int i = 16; i < 32; i++) {
        computerPlayer.addTileToHand(m_boneyard[i]);
    }
    for (int i = 31; i >= 0; i--) {
        m_boneyard.removeTile(i);
    }
   // m_playerHand.printHand();
    //std::cout << std::endl << "Computer Hand:" << std::endl;
   // m_computerHand.printHand();
   // std::cout << std::endl << "Bone yard:" << std::endl;
   // m_boneyard.printHand();

}

void Round::startRound()
{
    //instantiate deck by creating all tiles. remove the current engine tile, and shuffle the deck and deal the tiles to player and comptuer.
    instantiateDeck();
    removeEngineTile();
    shuffleDeck();
    dealTiles();
    startTurn();
}

void Round::whoGoesFirst()
{
}

void Round::removeEngineTile()
{
    int engineValue = getNextEngineValue();
    m_boneyard.removeTile(engineValue, engineValue);
}

void Round::setEngineTile()
{
}

void Round::resetEngineQueue() {
    engineQueue.clear();
    for (int i = 0; i < 10; i++) {
        engineQueue.push_front(i);
    }
}

int Round::getNextEngineValue() {
    if (engineQueue.empty()) {
        resetEngineQueue();
    }
    int tmpVal = engineQueue.front();
    engineInt = tmpVal;
    engineQueue.pop_front();
    return tmpVal;
}

void Round::startTurn()
{
    do {
        //HUMAN TRAIN TURN
        std::string userInput;
        char userTrain;
        std::cout << "Player One's turn to play: \nPlayer One's Hand: \n";
        humanPlayer.printHand();
        std::cout << "\nChoose a tile in x-y format to play (ie - 0-0)";
        std::cin >> userInput;


        std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
        std::cin >> userTrain;
        userTrain = tolower(userTrain);

        //various testing code wil between this comment and the next one.
        //computerPlayer.setOrphanDouble();//human train should be unplayable.
        //computerPlayer.setOrphanDouble();
        //computerPlayer.resetOrphanDouble();
        //end of testing code


        checkOrphanDoubles();

        if (checkOrphanDoubles() == false) {
            computerTrainPlayable = computerPlayer.getTrainMarker();
            humanTrainPlayable = true;
        }
        if (userTrain == 'h' && getHumanTrainPlayable()) {
            if (humanPlayer.tileFitsOnTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48), engineInt) == false) {
                std::cout << "Error: the tile you entered: " << userInput << " is not a valid tile.\n";
                continue;
            }
            humanPlayer.addTileToTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48));
        }
        else if (userTrain == 'c' && getComputerTrainPlayable()) {
            computerPlayer.addTileToTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48));
        }
        else if (userTrain == 'm' && getMexicanTrainPlayable()) {
            std::cout << "Mexican train not implemented yet jeez. will ad later";
        }
        humanPlayer.removeTileFromHand((int)userInput[0] - 48, (int)userInput[2] - 48);
        //BURBUR need to add error checking for userInput
        //check if zero'th and second digit are valid numbers(0-0)
        //add tile to train
        //remove tile from players hand
        //BURBUR have to make sure player has tile, and that tile matches to previous train entry.
        //BURBUR ERROR: ADDTILE FUNCTION ADDS TO HAND, AND WE NEED TO MAKE A FUNCTION TO ADD TO TRAIN.

        std::cout << "\n Trains: \n";
        printTrainAndEngine();


        std::cout << "\nYour Hand:\n";
        humanPlayer.printHand();

    } while (true);
    //computer turncomputer turncomputer turncomputer turncomputer turncomputer turncomputer turncomputer turncomputer turncomputer turncomputer turn
    std::string TEMPcomputerInput;
    std::cout << "\n\nComputers turn to play a tile: \n";
    std::cout << "Computer Hand: \n";
    computerPlayer.printHand();
    std::cout << "\n\n";
    std::cout << "Choose a tile in x-y format to play (ie - 0-0)";
    std::cin >> TEMPcomputerInput;
    computerPlayer.addTileToTrain(Tile((int)TEMPcomputerInput[0] - 48, (int)TEMPcomputerInput[2] - 48));
    computerPlayer.removeTileFromHand((int)TEMPcomputerInput[0] - 48, (int)TEMPcomputerInput[2] - 48);
    printTrainAndEngine();

    /*draw from boneyard test: print hand, print boneyard top, thenadd boneyard card to hand. then print hand again
    std::cout << "\n\n\n\n\nBoneyard get test";
    humanPlayer.addTileToHand(drawFromBoneyard());    */

}

void Round::printTrainAndEngine()
{
    humanPlayer.printTrain();   
    std::cout << engineInt << " - " << engineInt << " ";
    computerPlayer.printTrain();
}


//need error checking 
Tile Round::drawFromBoneyard()
{
    Tile tmpTile = m_boneyard.getTile(0);
    m_boneyard.removeTile(0);
    return tmpTile;
}

bool Round::getHumanTrainMarker()
{
    return this->humanPlayer.getTrainMarker();
}

bool Round::getComputerTrainMarker()
{
    return this->computerPlayer.getTrainMarker();
}

//if any train has orphan doulbe, return true. if it doesnt return false.
bool Round::checkOrphanDoubles()
{
    if (humanPlayer.getOrphanDouble() == true) {
        this->humanTrainPlayable = true;
        this->computerTrainPlayable = false;
        this->mexicanTrainPlayable = false;
        return true;
    }
    else if (computerPlayer.getOrphanDouble() == true) {
        this->humanTrainPlayable = false;
        this->computerTrainPlayable = true;
        this->mexicanTrainPlayable = false;
        return true;
    }
    else if (mexicanTrain.getOrphanDouble() == true) {
        this->humanTrainPlayable = false;
        this->computerTrainPlayable = false;
        this->mexicanTrainPlayable = true;
        return true;
    }
    return false;
}

void Round::checkHumansPlayableTrains()
{

}

void Round::checkComputerPlayableTrains()
{
}

void Round::resetPlayableTrains()
{
    this->humanTrainPlayable = false;
    this->computerTrainPlayable = false;
    this->mexicanTrainPlayable = false;
}

bool Round::getHumanTrainPlayable()
{
    return this->humanTrainPlayable;
}

bool Round::getComputerTrainPlayable()
{
    return this->computerTrainPlayable;
}

bool Round::getMexicanTrainPlayable()
{
    return this->mexicanTrainPlayable;
}




//validate tile
//validate usabel trains
//

//check if any train has orphan double, 
//check if op's train has marker

//getValidTrains()
//check if there is an orphan double on a train. if there, is all other trains are invalid.
//check if there is a marker on opponents train. if tehre is that becomes avalid train.
//

//optino 1- member variable booleans for round class
//option 2- normal boolean variables in function that get passed to function. would have to pass by reference.
//
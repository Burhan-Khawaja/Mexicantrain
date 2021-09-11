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
    std::string userInput;
    char userTrain;
    std::cout << "Player One's turn to play: \n";
    std::cout << "Player One's Hand: \n";
    humanPlayer.printHand();
    std::cout << "\n";
    std::cout << "Choose a tile in x-y format to play (ie - 0-0)";
    std::cin >> userInput;
    std::cout << "Choose a train to play the tile on (h for human, c for computer, or m for mexican train): ";
    std::cin >> userTrain;


    //BURBUR need to add error checking for userInput
    //check if zero'th and second digit are valid numbers(0-0)
    //add tile to train
    //remove tile from players hand
    //BURBUR have to make sure player has tile, and that tile matches to previous train entry.
    if (isdigit(userInput[0]) && isdigit(userInput[2])) {
        //BURBUR ERROR: ADDTILE FUNCTION ADDS TO HAND, AND WE NEED TO MAKE A FUNCTION TO ADD TO TRAIN.
        humanPlayer.addTileToTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48));
        humanPlayer.removeTileFromHand((int)userInput[0] - 48, (int)userInput[2] - 48);
        std::cout << "\n Trains: \n";
        printTrainAndEngine();
        

        std::cout << "\nYour Hand:\n";
        humanPlayer.printHand();
    }

    //computer turn
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




//validate tile
//validate usabel trains
//

//check if any train has orphan double, 
//check if op's train has marker
#pragma once
#include "Computer.h"

Computer::Computer() {
        //playerHand.addTile(Tile(1, 1));
        //playerTrain.addTileFront(Tile(1, 1));
}

void Computer::addTileToHand(Tile tileToAdd) {
    playerHand.addTile(tileToAdd);
}

void Computer::addTileToTrain(Tile tileToAdd) {
    if (tileToAdd.getFirstNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToAdd.getSecondNumber());
        tileToAdd.swapNumbers();
    }
    else if (tileToAdd.getSecondNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToAdd.getFirstNumber());
    }
    playerTrain.addTileFront(tileToAdd);
}

//BURBUR NEED TO MO VE THIS FUNCTION TO PLAYER CLASS SO HUMAN CAN USE IT TOO.
int Computer::play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engine) {
    
    this->printGameState(humanPlayer, computerPlayer, mexicanTrain, boneyard, humanScore, computerScore, roundNumber, engine);

    //REMOVE ALL TILE SFROM HAND TO MAKE TESTING EASIER.
    //remove all tiles from players hand and add 1 unplayable tile for testing reasons.
    //int tempTestVal = computerPlayer->getHandSize();
    /*
    while (computerPlayer->getHandSize() > 0) {
        computerPlayer->removeTileFromHand(computerPlayer->getFirstHandTile().getFirstNumber(), computerPlayer->getFirstHandTile().getSecondNumber());
    }
    computerPlayer->addTileToHand(Tile(9, 9));
    computerPlayer->addTileToHand(Tile(9, 8));
    computerPlayer->addTileToHand(Tile(8, 8));
    computerPlayer->addTileToHand(Tile(8, 8));
    computerPlayer->addTileToHand(Tile(7, 8));
*/
    //COMNPUTER AI CODE BELOW
    //if mexican train playable:

    std::vector<Tile> tilesToPlay;
    std::vector<char> trainsToPlayOn;
    
    if (checkOrphanDoubles(humanPlayer, mexicanTrain) == false) {
        humanTrainPlayable = humanPlayer->getTrainMarker();
        this->computerTrainPlayable = true;
        this->mexicanTrainPlayable = true;
    }
    bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
    if (!validMove) {
        bool skipTurn = noPlayableTiles(humanPlayer, computerPlayer, mexicanTrain, boneyard);
        //BURBUR refactor this code
        if (skipTurn == false) {//drawn tile is not playable, skip turn after a marker is placed on train.
            this->setTrainMarker();
            return 0;
        }
        else {
            return 0;
        }
    }
    //BURBUR doesnt work since I might end up playing multiple tiles
    std::string reasoning = findBestMove(humanPlayer, computerPlayer, mexicanTrain, boneyard, tilesToPlay, trainsToPlayOn);
    interpretBestMove(tilesToPlay, trainsToPlayOn);
    if (!tilesToPlay.empty()) {
        for (int i = 0; i < tilesToPlay.size(); i++) {
            if (trainsToPlayOn[i] == 'c') {
                computerPlayer->addTileToTrain(tilesToPlay[i]);
            }
            else if (trainsToPlayOn[i] == 'h') {
                humanPlayer->addTileToTrain(tilesToPlay[i]);
            }
            else {
                //MEXICAN TRAIN 
                mexicanTrain.addTileBack(tilesToPlay[i]);
            }
            computerPlayer->removeTileFromHand(tilesToPlay[i].getFirstNumber(), tilesToPlay[i].getSecondNumber());
            if (computerPlayer->getHandSize() == 0) {
                //checkGameWon returns pips of human player.
                return checkGameWon(humanPlayer);
            }
        }
    }
    std::cout <<"\n\n" << interpretBestMove(tilesToPlay, trainsToPlayOn);
    tilesToPlay.clear();
    trainsToPlayOn.clear();
    /*
    //OLD TESTING CODE BELOW. CAN IGNORE.
    std::string userInput;
    computerPlayer->printHand();
    std::cout << "\n\nSelect tile to play: \n";
    std::cin >> userInput;

    char userTrain;
    std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
    std::cin >> userTrain;
    userTrain = tolower(userTrain);

    if (userTrain == 'h') {
        humanPlayer->addTileToTrain(Tile(userInput[0] - 48, userInput[2] - 48));
    }
    else if (userTrain == 'c') {
        computerPlayer->addTileToTrain(Tile(userInput[0] - 48, userInput[2] - 48));
    }
    else {//userTrain == m

        mexicanTrain.addTileBack(Tile(userInput[0] - 48, userInput[2] - 48));
    }*/
    return -1;


}
int Computer::checkGameWon(Player * humanPlayer)
{
    if (this->getHandSize() == 0) {
        std::cout << "\n\n\nyou lost! the computer won.\n\n\n";
        return humanPlayer->sumOfPips();
    }
}
/*
std::vector<Tile> Computer::getPlayableTiles(std::vector<Tile> playerHand, int trainEndNumber)
{
    std::vector<Tile> playableTiles;

    for (int i = 0; i < playerHand.size(); i++) {
        if (playerHand[i].getFirstNumber() == trainEndNumber) {
            playableTiles.push_back( Tile(playerHand[i].getFirstNumber(), playerHand[i].getSecondNumber() ) );
        }
        else if (playerHand[i].getSecondNumber() == trainEndNumber) {
            playableTiles.push_back(Tile(playerHand[i].getFirstNumber(), playerHand[i].getSecondNumber()));
        }
    }
    return playableTiles;
}
*/
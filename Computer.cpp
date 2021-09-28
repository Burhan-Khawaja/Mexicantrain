#pragma once
#include "Computer.h"

Computer::Computer() {
    this->playerTrain = {};
    this->playerHand = {};
    this->trainLastNumber = -1;
    humanTrainPlayable = false;
    computerTrainPlayable = false;
    mexicanTrainPlayable = false;}




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

int Computer::play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engine) {
    
    this->printGameState(humanPlayer, computerPlayer, mexicanTrain, boneyard, humanScore, computerScore, roundNumber, engine);

    std::vector<Tile> tilesToPlay;
    std::vector<char> trainsToPlayOn;
    
    if (checkOrphanDoubles(humanPlayer,computerPlayer, mexicanTrain) == false) {
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
    }

    findBestMove(humanPlayer, computerPlayer, mexicanTrain, boneyard, tilesToPlay, trainsToPlayOn);
    interpretBestMove(tilesToPlay, trainsToPlayOn);
    if (!tilesToPlay.empty()) {
        for (int i = 0; i < tilesToPlay.size(); i++) {
            if (trainsToPlayOn[i] == 'c') {
                computerPlayer->addTileToTrain(tilesToPlay[i]);
                if (computerPlayer->getTrainMarker()) {
                    computerPlayer->resetTrainMarker();
                }
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
    //user played 2 tiles, so theres a chance that there is 1 orphan double.
    if (trainsToPlayOn.size() >= 2) {
        if (trainsToPlayOn[0] != trainsToPlayOn[1]) {
            //train user played on arent equal to each other, so make the first train an orphan double
            if (trainsToPlayOn[0] == 'm') {
                mexicanTrain.setOrphanDouble();
            }
            else if (trainsToPlayOn[0] == 'c') {
                computerPlayer->setOrphanDouble();
            }
            else {
                humanPlayer->setOrphanDouble();
            }
        }
    }

    if (trainsToPlayOn.size() == 3) {
        if (trainsToPlayOn[1] != trainsToPlayOn[2]) {
            //train user played on arent equal to each other, so make the first train an orphan double
            if (trainsToPlayOn[1] == 'm') {
                mexicanTrain.setOrphanDouble();
            }
            else if (trainsToPlayOn[1] == 'c') {
                computerPlayer->setOrphanDouble();
            }
            else {
                humanPlayer->setOrphanDouble();
            }
        }

    }
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
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
int Computer::play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard) {
    //COMNPUTER AI CODE BELOW
    //if mexican train playable: 

    if (checkOrphanDoubles(humanPlayer, mexicanTrain) == false) {
        humanTrainPlayable = humanPlayer->getTrainMarker();
        this->computerTrainPlayable = true;
        this->mexicanTrainPlayable = true;
    }
    Tile tileToPlay;
    char trainToPlayOn;

    //BURBUR doesnt work since I might end up playing multiple tiles
    findBestMove(humanPlayer, computerPlayer, mexicanTrain, boneyard, tileToPlay, trainToPlayOn);

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
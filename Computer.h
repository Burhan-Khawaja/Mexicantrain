#pragma once
#include "Player.h"

class Computer : public Player {
public:    
    Computer() {
        //playerHand.addTile(Tile(1, 1));
        //playerTrain.addTileFront(Tile(1, 1));
    }
    void addTileToHand(Tile tileToAdd) {
        playerHand.addTile(tileToAdd);
    }
    void addTileToTrain(Tile tileToAdd) {
        playerTrain.addTileBack(tileToAdd);
    }
    int play(Player * humanPlayer, Player * computerPlayer, Train mexicanTrain, Hand boneyard) {
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
        }
        return -1;
    }

protected:
private:

};
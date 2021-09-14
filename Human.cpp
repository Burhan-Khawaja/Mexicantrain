#include "Human.h"
#include <iostream>

Human::Human() {

}

void Human::addTileToHand(Tile tileToAdd)
{
    playerHand.addTile(tileToAdd);
}

void Human::addTileToTrain(Tile tileToAdd) {
    playerTrain.addTileFront(tileToAdd);
}

//BURBUR CHANGE FUNCTION SO THAT IT TAKE AN ARGUMENT OF THE TILE ON THE TRAIN TO CHECK AGAINST, THAT WS THIS FUNCTION IS AGNOSTIC TOWARDS WHAT THE TRAIN IS.
/*
bool Human::tileFitsOnTrain(Tile tileToCheck, int engine) {
    if (playerTrain.isEmpty()) {
        std::cout << "Playe train is empty, functions are working properly.";
        if (tileToCheck.getFirstNumber() != engine && tileToCheck.getSecondNumber() != engine) {
            return false;
        }
        return true; 
    }
    //trainTileFirstNum and trainTileSecondNum will hold the values of the dominoes last placed on the train
    //this will make it easier to understand the if statement.
    int trainTileFirstNum = playerTrain.getFirstTile().getFirstNumber();
    int trainTileSecondNum = playerTrain.getFirstTile().getSecondNumber();
    Tile trainTile = playerTrain.getFirstTile();
    if (tileToCheck.getFirstNumber() != trainTileFirstNum && tileToCheck.getFirstNumber() != trainTileSecondNum && tileToCheck.getSecondNumber() != trainTileFirstNum && tileToCheck.getSecondNumber() != trainTileSecondNum) {
        return false;
    }
    return true;
}
*/

#include "Player.h"


bool Player::tileFitsOnTrain(Tile tileToCheck, int engineInt, Tile trainTile)
{
    /*
    if (trainTile.getFirstNumber() == -1 && trainTile.getSecondNumber() == -1) {
        if (tileToCheck.getFirstNumber() != engineInt && tileToCheck.getSecondNumber() != engineInt) {
            return false;
        }
        return true;
    }
    //trainTileFirstNum and trainTileSecondNum will hold the values of the dominoes last placed on the train
    //this will make it easier to understand the if statement.
    int trainTileFirstNum = trainTile.getFirstNumber();
    int trainTileSecondNum = trainTile.getSecondNumber();
    //what is this line of code? doesnt look like its usedTile trainTile = playerTrain.getFirstTile();
    if (tileToCheck.getFirstNumber() != trainTileFirstNum && tileToCheck.getFirstNumber() != trainTileSecondNum && tileToCheck.getSecondNumber() != trainTileFirstNum && tileToCheck.getSecondNumber() != trainTileSecondNum) {
        return false;
    }
    return true;*/
    //BURBUR refactor this code what is this garbage? please god dont hand this into Professor Kumar. PRofessor if you see this im sorry.
    if (playerTrain.getTrainEndNumber() == -1) {
        if (tileToCheck.getFirstNumber() != engineInt && tileToCheck.getSecondNumber() != engineInt) {
            return false;
        }

        if (tileToCheck.getFirstNumber() == engineInt) {
            playerTrain.setTrainEndNumber(engineInt, tileToCheck.getSecondNumber());
        }
        else if (tileToCheck.getSecondNumber() == engineInt) {
            playerTrain.setTrainEndNumber(engineInt, tileToCheck.getFirstNumber());
        }
        return true;
    }
    if (tileToCheck.getFirstNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(engineInt, tileToCheck.getSecondNumber());
        return true;
    }
    else if (tileToCheck.getSecondNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(engineInt, tileToCheck.getFirstNumber());
        return true;
    }

    return false;
}
//tileFitsOnTrain new algo- 
//should compare tileToCheck against train last number, make aget function for it.
//if the first number is == to the train last number, set the second number to be the new train last number.

//if last train number is -1, then we have to compare the values of the tile we are adding to the engineint and see if it fits
//else, we check if the first number is equal to the hanign train tile. if it is, then set the second number to be the new hanging train number
//otherwise, we check if the second is equal to the hanging train tile. if it is, set  the first number to be the new hanigng train number.
void Player::printTrain()
{
    playerTrain.printTrain();
}

void Player::printHand() {
    playerHand.printHand();
}

void Player::removeTileFromHand(int value1, int value2)
{
    playerHand.removeTile(value1, value2);
}

bool Player::getTrainMarker()
{
    return playerTrain.getMarker();
}

bool Player::getOrphanDouble()
{
    return this->playerTrain.getOrphanDouble();
}

bool Player::isTrainEmpty()
{
    return this->playerTrain.isEmpty();
}

Tile Player::getFirstTrainTile()
{
    return this->playerTrain.getFirstTile();
}

Tile Player::getLastTrainTile()
{
    return this->playerTrain.getLastTile();
}

void Player::setTrainEndNumber(int engineInt, int newEndNumber)
{
    playerTrain.setTrainEndNumber(engineInt, newEndNumber);
}


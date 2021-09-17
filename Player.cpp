#include "Player.h"


bool Player::tileFitsOnTrain(Tile tileToCheck, Tile trainTile)
{
    //BURBUR refactor this code what is this garbage? please god dont hand this into Professor Kumar. PRofessor if you see this im sorry.
    //BURBUR REMOVED engineint part since we set the train ends number in constructor. 
    /*
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
    */
    if (tileToCheck.getFirstNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToCheck.getSecondNumber());
        return true;
    }
    else if (tileToCheck.getSecondNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToCheck.getFirstNumber());
        return true;
    }
    std::cout << "Error: The tile you selected does not fit on the train\n";
    return false;
}

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

void Player::setTrainEndNumber( int newEndNumber)
{
    playerTrain.setTrainEndNumber(newEndNumber);
}

int Player::getTrainEndNumber()
{
    return this->playerTrain.getTrainEndNumber();
    //return this->trainLastNumber;
}

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

Tile Player::getFirstHandTile()
{
    return this->playerHand[0];
}



bool Player::verifyTileChoice(std::string userInput)
{
    //have to check if string is greater then 3 because of null character ('\0')
    if (userInput.length() > 3) {
        std::cout << "\nError: The tile you entered " << userInput << " is too long to be a valid tile\n";
        return false;
    }
    else if (userInput.size() <= 2) {
        std::cout << "\nError: The tile you entered " << userInput << " is too short to be a valid tile\n";
        return false;
    }
    else if (!isdigit(userInput[0]) || !isdigit(userInput[2])) {
        std::cout << "\nError: The tile " << userInput << " Does not have a valid format, one of the characters is not a number\n";
        return false;
    }
    else if (userInput[1] != '-') {
        std::cout << "\nError: The tile you entered " << userInput << " must be seperated by a '-'\n";
        return false;
    }
    return true;
}

//Function was making sure user entered valid value for the train to play, but also that the tile fit on the train.
//dont do that. changing function so it only checks if the user is able to play on the train selected. we will handle checking if the tile fits on the train with
//tilefitsontrain function.
bool Player::validateTrainChoice(char userTrain)
{
    if (userTrain != 'h' && userTrain != 'c' && userTrain != 'm') {
        std::cout << "Error: you entered an invalid train.";
        return false;
    }
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

bool Player::getHumanTrainPlayable()
{
    return this->humanTrainPlayable;
}

bool Player::getComputerTrainPlayable()
{
    return this->computerTrainPlayable;
}

bool Player::getMexicanTrainPlayable()
{
    return this->mexicanTrainPlayable;
}

bool Player::checkOrphanDoubles(Player* oppositeTrain, Train mexicanTrain)
{
    if (getOrphanDouble() == true) {
        this->humanTrainPlayable = true;
        this->computerTrainPlayable = false;
        this->mexicanTrainPlayable = false;
        return true;
    }
    else if (oppositeTrain->getOrphanDouble() == true) {
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
    return false;
}

int Player::getHandSize()
{
    return this->playerHand.getSize();
}

bool Player::hasTile(Tile userInputAsTile)
{
    for (int i = 0; i < playerHand.getSize(); i++) {
        if (playerHand[i].getFirstNumber() == userInputAsTile.getFirstNumber() && playerHand[i].getSecondNumber() == userInputAsTile.getSecondNumber()) {
            return true;
        }
    }
    return false;
}



#pragma once
#include "Round.h"


Round::Round()
{
    this->humanPlayer = new Human;
    this->computerPlayer = new Computer;
    computerPlayer->setTrainEndNumber(this->engineInt );
    humanPlayer->setTrainEndNumber(this->engineInt);
    mexicanTrain.setTrainEndNumber(this->engineInt);

}

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
        humanPlayer->addTileToHand(m_boneyard[i]);
    }    
    for (int i = 16; i < 32; i++) {
        computerPlayer->addTileToHand(m_boneyard[i]);
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
    setEngineTile();
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
    humanPlayer->setTrainEndNumber(engineInt);
    computerPlayer->setTrainEndNumber(engineInt);
    mexicanTrain.setTrainEndNumber(engineInt);
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
        std::cout << "\n\n\n\Current Trains:\n";
        printTrainAndEngine();
        humanPlayer->play(this->humanPlayer, this->computerPlayer, this->mexicanTrain, this->m_boneyard);
        std::cout << "\n\n\t\t\t\tComputer Turn!";
        std::cout << "\n\nCurrent Trains:\n";
        printTrainAndEngine();        
        std::cout << "\n\n\n\n";
        computerPlayer->play(this->humanPlayer, this->computerPlayer, this->mexicanTrain, this->m_boneyard);
        /*
        std::cout << "\nCurrent Trains: \no
        printTrainAndEngine();
        std::cout << "\n\n\n";
        if (checkOrphanDoubles() == false) {
            computerTrainPlayable = computerPlayer.getTrainMarker();
            humanTrainPlayable = true;
        }
        //should move this somehwere else. possibly in the constructor of the class to start the round class. along with other things
        //like 
        if (humanPlayer.isTrainEmpty()) {
            humanPlayer.setTrainEndNumber(this->engineInt, this->engineInt);
        }
        if (computerPlayer.isTrainEmpty()) {
            computerPlayer.setTrainEndNumber(this->engineInt, this->engineInt);
        }

        bool playerHasMove;

        if (getHumanTrainPlayable() && humanPlayer.playerHasMove(humanPlayer.getTrainEndNumber())) {
            playerHasMove = true;
        }

        if (getComputerTrainPlayable() && humanPlayer.playerHasMove(computerPlayer.getTrainEndNumber())) {
            playerHasMove = true;
        }

        if (getMexicanTrainPlayable()) {

        }

        if (playerHasMove == false) {
            std::cout << "Error: You have no valid move, Drawing a tile from the boneyard.";
            Tile tmpTile = drawFromBoneyard();
            if (tmpTile.getFirstNumber() == -1) {
                std::cout << "Boneyard is empty, so skipping turn.";
                //break;
            }
            std::cout << "The tile you drew from the boneyard is: ";
            tmpTile.printTile();
        }

        Tile userTile = humanPlayer.play(this->humanTrainPlayable, this->computerTrainPlayable, this->mexicanTrainPlayable);

        char userTrain;
        std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
        std::cin >> userTrain;
        userTrain = tolower(userTrain);
        if (!validateTrainChoice(userTrain, userTile)) {
            continue;
        }
/*        if (userTrain == 'h' && getHumanTrainPlayable()) {
            if (humanPlayer.tileFitsOnTrain(userTile, engineInt, humanPlayer.getFirstTrainTile()) == false) {
                std::cout << "Error: the tile you entered: ";
                userTile.printTile();
                std::cout << " is not a valid tile since it does not fit on the human train.\n";
                continue;
            }
            humanPlayer.addTileToTrain(userTile);
        }
        else if (userTrain == 'c' && getComputerTrainPlayable()) {
            if (computerPlayer.tileFitsOnTrain(userTile, engineInt, computerPlayer.getLastTrainTile()) == false) {
                std::cout << "Error: the tile you entered: ";
                userTile.printTile();
                std::cout << " is not a valid tile.\n";
                continue;
            }
            computerPlayer.addTileToTrain(userTile);
        }
        else if (userTrain == 'm' && getMexicanTrainPlayable()) {
            std::cout << "Mexican train not implemented yet jeez. will ad later";
            if (mexicanTrain.isEmpty()) {

            }
        }
        else {
            std::cout << "Error: The train you  selected is unplayable." << std::endl;
            continue;
        }
        humanPlayer.removeTileFromHand(userTile.getFirstNumber(), userTile.getSecondNumber());
        //BURBUR have to make sure player has tile, 

        //double check. If the player doesnt play a double, then their turn is over.
        if (userTile.getFirstNumber() == userTile.getSecondNumber()) {
            //humanPlayer.playedDoubleTile(userInput);
            playedDoubleTile(userTrain);
        }
        */
    } while (true);
}

void Round::printTrainAndEngine()
{
    computerPlayer->printTrain();
    std::cout << engineInt << " - " << engineInt << " ";
    humanPlayer->printTrain();
    std::cout << "\nMexican Train: ";
    mexicanTrain.printTrain();
}


//need error checking 
Tile Round::drawFromBoneyard()
{
    if (m_boneyard.getSize() == 0) {
        return Tile(-1, -1);
    }
    Tile tmpTile = m_boneyard.getTile(0);
    m_boneyard.removeTile(0);
    return tmpTile;
}

bool Round::getHumanTrainMarker()
{
    return this->humanPlayer->getTrainMarker();
}

bool Round::getComputerTrainMarker()
{
    return this->computerPlayer->getTrainMarker();
}

//if any train has orphan doulbe, return true. if it doesnt return false.
//BURBUR MOVED TO PLAYER CLASS REMOVE LATER
bool Round::checkOrphanDoubles()
{
    /*
    if (humanPlayer->getOrphanDouble() == true) {
        this->humanTrainPlayable = true;
        this->computerTrainPlayable = false;
        this->mexicanTrainPlayable = false;
        return true;
    }
    else if (computerPlayer->getOrphanDouble() == true) {
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
    */
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

bool Round::verifyTileChoice(std::string userInput)
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

bool Round::playerHasMove()
{
    return false;
}

int Round::getComputerTrainEndNumber()
{
    return computerPlayer->getTrainEndNumber();
}

int Round::getHumanTrainEndNumber()
{
    return humanPlayer->getTrainEndNumber();
}

void Round::playedDoubleTile(char userInput)
{
    bool validTileSelected;
    do {
        bool playerHasMove = false;
        if (getHumanTrainPlayable() && humanPlayer->playerHasMove(humanPlayer->getTrainEndNumber())) {
            playerHasMove = true;
        }
        if (getComputerTrainPlayable() && humanPlayer->playerHasMove(computerPlayer->getTrainEndNumber())) {
            playerHasMove = true;
        }
        if (getMexicanTrainPlayable()) {

        }

        if (playerHasMove == false) {
            std::cout << "Error player has no valid move. Train has become an orphan double.";
            if (userInput == 'm') {
                mexicanTrain.setOrphanDouble();
            }
            else if (userInput == 'c') {
                computerPlayer->setOrphanDouble();
            }
            else {
                humanPlayer->setOrphanDouble();
            }
        }
        std::string secondUserTile;
        std::cout << "\nYou have played a double tile, you are allowed to play another tile\n";
        humanPlayer->printHand();
        std::cout << "Choose a tile to play in 0-0 format: \n";
        std::cin >> secondUserTile;
        if (!verifyTileChoice(secondUserTile)) {
            std::cout << " Restarting Turn.\n\n";
        }
        char secondUserTrain;
        if(!verifyTileChoice(secondUserTile)) {
            std::cout << " Restarting Turn.\n\n";
        }
        std::cout << "\nChoose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
        std::cin >> secondUserTrain;
        secondUserTrain = tolower(secondUserTrain);
        validateTrainChoice(secondUserTrain, Tile(secondUserTile[0]-48, secondUserTile[2]-48));
        validTileSelected = false;
    } while (validTileSelected = true);
}

bool Round::validateTrainChoice(char userTrain, Tile userTile)
{
    /*
    if (userTrain == 'h' && getHumanTrainPlayable()) {
        if (humanPlayer->tileFitsOnTrain(userTile, engineInt, humanPlayer->getFirstTrainTile()) == false) {
            std::cout << "Error: the tile you entered: ";
            userTile.printTile();
            std::cout << " is not a valid tile since it does not fit on the human train.\n";
            return false;
        }
        humanPlayer->addTileToTrain(userTile);
    }
    else if (userTrain == 'c' && getComputerTrainPlayable()) {
        if (computerPlayer->tileFitsOnTrain(userTile, engineInt, computerPlayer->getLastTrainTile()) == false) {
            std::cout << "Error: the tile you entered: ";
            userTile.printTile();
            std::cout << " is not a valid tile.\n";
            return false;
        }
        computerPlayer->addTileToTrain(userTile);
    }
    else if (userTrain == 'm' && getMexicanTrainPlayable()) {
        std::cout << "Mexican train not implemented yet jeez. will ad later";
        if (mexicanTrain.isEmpty()) {

        }
    }
    else {
        std::cout << "Error: The train you selected does not exist or is unplayable." << std::endl;
        return false;
    }
    
    return true;
    */
    return false;
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


/*NEED TO DO:
Make sure we have afunction to check if player has a valid turn. Easiest way would be to check if there exists a tile that matches
the hanging tile value.
if they dont have a turn, make them draw from the boneyard and check if they can play that tile on the ligible trains.

-the while(human turn = true) loop thing I have isnt how th epogram should be. when the  player plays a double they should only be allowed to play 1 til
    unless they have another double


bool playerHasMove();
check what trains are eligible. 
if statement that will check what trains are playable, and if they  are playable, then 
call playerHasMove() with the trainTile and engine unit incase train is empty. need to access the players hand. 
might have to move the playerHasMove class to player class. 
playerHasmove(int engineUnit, computer/human/mexicanTrain.hangingNumber(),
does any tile in the players hand match the trains hanging number?
*/

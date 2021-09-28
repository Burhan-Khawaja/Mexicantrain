#include "Player.h"


Player::Player()
{
    this->playerTrain = {};
    this->playerHand = {};
    this->trainLastNumber = -1;
    //these 3 booleans dictate weather the player can play on each train.
    this->humanTrainPlayable = false;
    this->computerTrainPlayable = false;
    this->mexicanTrainPlayable = false;
}



void Player::addTileToHand(Tile tileToAdd)
{
    playerHand.addTile(tileToAdd);
}

bool Player::tileFitsOnTrain(Tile tileToCheck, int trainEndNumber)
{    
    if (tileToCheck.getFirstNumber() == trainEndNumber) {
       return true;
    }
    else if (tileToCheck.getSecondNumber() == trainEndNumber) {
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

void Player::setTrainMarker()
{
    playerTrain.setMarker();
}

void Player::resetTrainMarker()
{
    this->playerTrain.clearMarker();
}

bool Player::getOrphanDouble()
{
    return this->playerTrain.getOrphanDouble();
}

void Player::setOrphanDouble()
{
    playerTrain.setOrphanDouble();
}

void Player::resetOrphanDouble()
{
    playerTrain.resetOrphanDouble();
}

/*buurbur burbur commented out functions dell8er
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
*/
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

bool Player::existsValidMove(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain)
{
    bool validMove = false;
    if (this->humanTrainPlayable && playerHasMove(humanPlayer->getTrainEndNumber())) {
        validMove = true;
    }
    if (this->computerTrainPlayable && playerHasMove(computerPlayer->getTrainEndNumber())) {
        validMove = true;
    }
    if (this->mexicanTrainPlayable && playerHasMove(mexicanTrain.getTrainEndNumber())) {
        validMove = true;
    }
    return validMove;
}
/*
Tile Player::getFirstHandTile()
{
    return this->playerHand[0];
}
*/


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

void Player::setHumanTrainPlayable()
{
    this->humanTrainPlayable = true;
}

bool Player::getComputerTrainPlayable()
{
    return this->computerTrainPlayable;
}

void Player::setComputerTrainPlayable()
{
    this->computerTrainPlayable = true;
}

bool Player::getMexicanTrainPlayable()
{
    return this->mexicanTrainPlayable;
}

bool Player::checkOrphanDoubles(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain)
{
    bool orphanDouble = false;
    //1- check if there exists any orphan double on a train
    if (humanPlayer->getOrphanDouble() == true || computerPlayer->getOrphanDouble() == true || mexicanTrain.getOrphanDouble() == true) {
        //make all trains unplayable. later we will check which trains have orphan doubles and set them as the only trains playable
        this->humanTrainPlayable = false;
        this->computerTrainPlayable = false;
        this->mexicanTrainPlayable = false;
    }
    if (humanPlayer->getOrphanDouble() == true) {
        std::cout << "\nThere is an orphan double on the human train.\n";
        this->humanTrainPlayable = true;
        //this->computerTrainPlayable = false;
        //this->mexicanTrainPlayable = false;
        orphanDouble = true;
    }
    if (computerPlayer->getOrphanDouble() == true) {
        std::cout << "\nThere is an orphan double on the computer train.\n";

        //this->humanTrainPlayable = false;
        this->computerTrainPlayable = true;
        //this->mexicanTrainPlayable = false;
        orphanDouble = true;
    }
    if (mexicanTrain.getOrphanDouble() == true) {
        std::cout << "\nThere is an orphan double on the mexican train.\n";
        //this->humanTrainPlayable = false;
        //this->computerTrainPlayable = false;
        this->mexicanTrainPlayable = true;
        orphanDouble = true;
    }
    return orphanDouble;
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

//true- tile is drawn and playable
//false- tile not drawn, or unlayable and user has to skip turn.
bool Player::noPlayableTiles(Player * humanPlayer, Player * computerPlayer, Train & mexicanTrain, Hand & boneyard)
{
    if (boneyard.getSize() == 0) {
        std::cout << "Boneyard is empty, a marker is placed on your train";
        this->setTrainMarker();
        return false;
    }
    else {
        Tile boneyardTile = boneyard.getTile(0);
        boneyard.removeTile(0);
        this->addTileToHand(boneyardTile);
        bool validMove = this->existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
        if (!validMove) {
            std::cout << "You have no valid moves after taking the tile ";
            boneyardTile.printTile();
            std::cout << " from the boneyard.\nA marker has been place on your train.";
            this->setTrainMarker();
            return false;
        }
        else {//player has valid move.
            std::cout << "The tile drawn from the boneyard, ";
            boneyardTile.printTile();
            std::cout << " is playable. restarting turn.";
            return true;
        }
    }
}

int Player::sumOfPips()
{
    int total = 0;
    for (int i = 0; i < playerHand.getSize(); i++) {
        total += playerHand[i].getFirstNumber();
        total += playerHand[i].getSecondNumber();
    }
    return total;
}

void Player::clearData()
{
    this->playerTrain.clearTrain();
    this->playerHand.clearHand();
}

Tile Player::playerTileChoice()
{
    std::string userInput;
    std::cout << "\nChoose a tile in x-y format to play (ie - 0-0)";
    std::cin >> userInput;

    if (!verifyTileChoice(userInput)) {
        return Tile(-1, -1);
    }

    Tile userInputAsTile = Tile(userInput[0] - 48, userInput[2] - 48);
    if (!hasTile(userInputAsTile)) {
        std::cout << "\n\nError: you do not have that tile. Restarting Move. \n\n\n\n\n";
        return Tile(-1, -1);
    }

    return Tile(userInput[0] - 48, userInput[2] - 48);
}

const std::deque<Tile> Player::getTrain()
{
    return this->playerTrain.getTrainDeque();
}

const std::vector<Tile> Player::getHand()
{
    return this->playerHand.getHand();
}

void Player::findBestMove(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, std::vector<Tile>& bestTiles, std::vector<char>& trains)
{
    std::string bestMoveExplination = "";
    bool turnFinished = false;
    //computerPlayer->addTileToHand(Tile(9, 9));
    //stores what tiles the computer will play. either 1 single tile, a double and a non doubl, or 2 doubles and a non double.
    std::vector<Tile> tilesPlayed;
    std::vector<Tile> mexicanPlayableTiles;
    std::vector<Tile> humanPlayableTiles;
    std::vector<Tile> computerPlayableTiles;

    std::vector<Tile> mexicanDoubles;
    std::vector<Tile> humanDoubles;
    std::vector<Tile> computerDoubles;
    //create a temporary hand that we can change and see what moves are available without changing the players actual hand.
    std::vector<Tile> tmpVector = this->getHand();
    Hand tempPlayerHand;
    for (int i = 0; i < tmpVector.size(); i++) {
        tempPlayerHand.addTile(tmpVector[i]);
    }
    int doublesPlayed = 0;
    
    
    do {
        mexicanPlayableTiles.clear();
        humanPlayableTiles.clear();
        computerPlayableTiles.clear();
        mexicanDoubles.clear();
        humanDoubles.clear();
        computerDoubles.clear();
        //check if we have a valid move
        /*
        bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
        if (!validMove) {
            bool skipTurn = noPlayableTiles(humanPlayer, computerPlayer, mexicanTrain, boneyard);
            if (skipTurn == false) {//drawn tile is not playable, skip turn after a marker is placed on train.
                this->setTrainMarker();
                return 0;
            }
        }
        BURBUR we commented this out, but should im plement it here.s*/
        if (this->getMexicanTrainPlayable()) {
            mexicanPlayableTiles = getPlayableTiles(tempPlayerHand.getHand(), mexicanTrain.getTrainEndNumber());
        }
        if (this->getComputerTrainPlayable()) {
            computerPlayableTiles = getPlayableTiles(tempPlayerHand.getHand(), computerPlayer->getTrainEndNumber());
        }
        if (this->getHumanTrainPlayable()) {
            humanPlayableTiles = getPlayableTiles(tempPlayerHand.getHand(), humanPlayer->getTrainEndNumber());
        }

        //search for all double tiles.
        for (int i = 0; i < mexicanPlayableTiles.size(); i++) {
            if (mexicanPlayableTiles[i].isDouble()) {
                mexicanDoubles.push_back(mexicanPlayableTiles[i]);
            }
        }

        for (int i = 0; i < humanPlayableTiles.size(); i++) {
            if (humanPlayableTiles[i].isDouble()) {
                humanDoubles.push_back(humanPlayableTiles[i]);
            }
        }

        for (int i = 0; i < computerPlayableTiles.size(); i++) {
            if (computerPlayableTiles[i].isDouble()) {
                computerDoubles.push_back(computerPlayableTiles[i]);
            }
        }

        //Start playing tiles. if the mexican train is playable, check if we can play a double on it. if we cant, play a normal tile
        //BUBUR THIS SHOULD BE IT. we should check for other playable doubles.
        //PLAY ANY VALID DOUBLE TILES
        if (getMexicanTrainPlayable() & !mexicanDoubles.empty() && doublesPlayed < 2) {
            //BURBUR dont want to add tiles yet to trains.mexicanTrain.addTileBack(mexicanDoubles[0]);
            tilesPlayed.push_back(mexicanDoubles[0]);
            if (mexicanDoubles[0].getFirstNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(mexicanDoubles[0].getSecondNumber());
            }
            else if (mexicanDoubles[0].getSecondNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(mexicanDoubles[0].getFirstNumber());
                mexicanDoubles[0].swapNumbers();
            }
            tempPlayerHand.removeTile(mexicanDoubles[0].getFirstNumber(), mexicanDoubles[0].getSecondNumber());
            bestTiles.push_back(mexicanDoubles[0]);
            trains.push_back('m');
            doublesPlayed++;
            continue;
        }
        else if (getHumanTrainPlayable() && !humanDoubles.empty() && doublesPlayed < 2) {
            tempPlayerHand.removeTile(humanDoubles[0].getFirstNumber(), humanDoubles[0].getSecondNumber());
            bestTiles.push_back(humanDoubles[0]);
            trains.push_back('h');
            doublesPlayed++;
            continue;
        }
        else if (getComputerTrainPlayable() && !computerDoubles.empty() && doublesPlayed < 2) {
            //computerPlayer->addTileToTrain(computerDoubles[0]);
            tempPlayerHand.removeTile(computerDoubles[0].getFirstNumber(), computerDoubles[0].getSecondNumber());
            bestTiles.push_back(computerDoubles[0]);
            trains.push_back('c');
            doublesPlayed++;
            continue;

        }
        

        //play valid single tiles
        if (getMexicanTrainPlayable() && !mexicanPlayableTiles.empty()) {
            /*if (mexicanPlayableTiles[0].getFirstNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(mexicanPlayableTiles[0].getSecondNumber());
            }
            else if (mexicanPlayableTiles[0].getSecondNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(mexicanPlayableTiles[0].getFirstNumber());
                mexicanPlayableTiles[0].swapNumbers();
            }*/
            //mexicanTrain.addTileBack(mexicanPlayableTiles[0]);
            bestTiles.push_back(mexicanPlayableTiles[0]);          
            tempPlayerHand.removeTile(mexicanPlayableTiles[0].getFirstNumber(), mexicanPlayableTiles[0].getSecondNumber());
            trains.push_back('m');
            //return bestMoveExplination;
            return;
        }
        if (getHumanTrainPlayable() && !humanPlayableTiles.empty()) {
            bestTiles.push_back(humanPlayableTiles[0]);
            trains.push_back('h');
            //return bestMoveExplination;
            return;
        }
        if (getComputerTrainPlayable() && !computerPlayableTiles.empty()) {
            bestTiles.push_back(computerPlayableTiles[0]);
            trains.push_back('c');
            //return bestMoveExplination;
            return;
        }
        //return bestMoveExplination;
        return;
    } while (turnFinished == false); 
    
}

/*if (userInputAsTile.getFirstNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(userInputAsTile.getSecondNumber());
            }
            else if (userInputAsTile.getSecondNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(userInputAsTile.getFirstNumber());
                userInputAsTile.swapNumbers();
            }
            mexicanTrain.addTileBack(userInputAsTile); 
*/
std::vector<Tile> Player::getPlayableTiles(std::vector<Tile> playerHand, int trainEndNumber)
{
    std::vector<Tile> playableTiles;

    for (int i = 0; i < playerHand.size(); i++) {
        if (playerHand[i].getFirstNumber() == trainEndNumber) {
            playableTiles.push_back(Tile(playerHand[i].getFirstNumber(), playerHand[i].getSecondNumber()));
        }
        else if (playerHand[i].getSecondNumber() == trainEndNumber) {
            playableTiles.push_back(Tile(playerHand[i].getFirstNumber(), playerHand[i].getSecondNumber()));
        }
    }
    return playableTiles;
}

void Player::printGameState(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engineInt)
{
    std::cout << "=================================================================\n";
    std::cout << "\n\t         Round: " << roundNumber;
    std::cout << "\nHuman Score: " << humanScore;
    std::cout << "\t\t\tComputer Score: " << computerScore;
    std::cout << "\nTrains: \n";
    if (computerPlayer->getTrainMarker()) {
        std::cout << "M ";
    }
    computerPlayer->printTrain();
    std::cout << " " << engineInt << " - " << engineInt << " ,";
    humanPlayer->printTrain();
    if (humanPlayer->getTrainMarker()) {
        std::cout << " M";
    }
    std::cout << "\nMeixcan Train: ";
    mexicanTrain.printTrain();
    std::cout << "\n\nHuman players hand: \n";
    humanPlayer->printHand();
    std::cout << "\n\nComputer Players Hand: \n";
    computerPlayer->printHand();
    std::cout << "\nNext boneyard tile: ";
    if (boneyard.getSize() != 0) {
        boneyard.getTile(0).printTile();
    }
    else {
        std::cout << "Empty";
    }
    std::cout << "\n\n";

}

std::string Player::interpretBestMove(std::vector<Tile>& bestTiles, std::vector<char>& trains)
{
    std::string explination;
    //print out the doubles we played.
    for (int i = 0; i < bestTiles.size(); i++) {
        if (bestTiles[i].isDouble()) {
            explination += std::to_string(bestTiles[i].getFirstNumber()) + " - " + std::to_string(bestTiles[i].getSecondNumber());
            explination += " was played on the ";
            if (trains[i] == 'm') {
                explination += "mexican";
            }
            else if (trains[i] == 'c') {
                explination += "computer";
            }
            else {
                explination += "human";
            }
            explination += " train because it was a valid double tile.";
        }
    }
    
    if (!bestTiles.back().isDouble()) {
        explination += std::to_string(bestTiles.back().getFirstNumber()) + " - " + std::to_string(bestTiles.back().getSecondNumber());
        explination += " was played on the ";
        if (trains.back() == 'm') {
            explination += "mexican";
        }
        else if (trains.back() == 'c') {
            explination += "computer";
        }
        else {
            explination += "human";
        }

        explination += " train because it was the largest tile.\n\n";
    }
    return explination;
}

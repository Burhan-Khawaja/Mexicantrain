#pragma once
#include "Round.h"


Round::Round()
{
    this->humanPlayer = new Human;
    this->computerPlayer = new Computer;
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

int Round::startRound(bool serialiedStart, int humanScore, int computerScore, int roundNumber)
{
    //step 1- check if we are starting the game from a fle we already loaded.
    //if we are, then we do not have ot instantiate deck or remove engine tile, shuffle the deck etc. we can just start
    //if we are NOT loading the game from a file, we must setup the game properly.
    //instantiate deck by creating all tiles. remove the current engine tile, and shuffle the deck and deal the tiles to player and comptuer.
    if(!serialiedStart){
        instantiateDeck();
        removeEngineTile();
        shuffleDeck();
        dealTiles();
        setEngineTile();
        whoGoesFirst(humanScore, computerScore);
    }
    int pipsValue = startTurn(humanScore, computerScore, roundNumber);
    //game is over, remove all lingering data incase user wants to play another round.
    //HOWEVER if we want to save the game, then we dont want to clean the data. we want to keep it
    //so we check if the pipsValue returned is -10, which is our value for a user choosing to save the game
    if (pipsValue != -10) {
        cleanData();
    }

    return pipsValue;
}



void Round::whoGoesFirst(int humanScore, int computerScore)
{
    if (humanScore < computerScore) {
        std::cout << "The human has a lower score, so you get to go first. \n";
        setHumanTurn();
        return;
    }
    else if (computerScore < humanScore) {
        std::cout << "The computer has a lower score, so the computer goes first.\n";
        setComputerTurn();
        return;
    }
    //coin flip: 
    int userChoice;
    do {
        std::cout << "\n\nBoth players have the same score.\nA coint toss will determine who goes first.\n";
        std::cout << "Enter 1 for heads, 2 for tails: ";
        std::cin >> userChoice;
        if (userChoice != 1 && userChoice != 2) {
            std::cout << "Error: invalid value entered. Try again.\n";
        }
    } while (userChoice != 1 && userChoice != 2);

    int randomNum = (rand() % 2) + 1;
    if (randomNum == userChoice) {
        std::cout << "\nCongratulations! you guessed correctly and you have the first turn.\n\n";
        setHumanTurn();
    }
    else {
        std::cout << "\nSorry, you guessed wrong and the computer goes first.\n\n";
        setComputerTurn();
    }
}

//remove the engine tile from the boneyard
void Round::removeEngineTile()
{
    int engineValue = getNextEngineValue();
    m_boneyard.removeTile(engineValue, engineValue);
}

//BURBUR NOT SETTING ENGINE TILE, SHOULD BE RENAMED TO SETTRAINENDNUMBER
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

//used for when we load a game.
void Round::setEngineValue(int engineVal)
{
    if (engineQueue.empty()) {
        resetEngineQueue();
    }
    while (this->engineInt != engineVal) {
        engineInt = getNextEngineValue();
    }
}

int Round::startTurn(int humanScore, int computerScore, int roundNumber)
{
    //
    int humanPipsLeft = 0;
    int computerPipsLeft = 0;

    do {
        //BURBUR remove commented code since its doing stuff with the old text menu thing.
        // std::cout << "\n\n\n\Current Trains:\n";
        //printTrainAndEngine();
        if (humanTurn) {
            char userChoice = outputMenu(true);
            if (userChoice == 's') {
                return -10; //-10 is the code to save game
            }
        
            computerPipsLeft = humanPlayer->play(this->humanPlayer, this->computerPlayer, this->mexicanTrain, this->m_boneyard, humanScore, computerScore, roundNumber, this->getEngineInt());
            setComputerTurn();
        }


        if (computerPipsLeft > 0) {
            humanWon = true;
            return computerPipsLeft;
        }
        
        //BURBUR need to add dealing with user choice ehre like above.
        if (computerTurn) {
            outputMenu(false);
       
            humanPipsLeft = computerPlayer->play(this->humanPlayer, this->computerPlayer, this->mexicanTrain, this->m_boneyard, humanScore, computerScore, roundNumber, this->getEngineInt());
            setHumanTurn();
        }

        if (humanPipsLeft > 0) {
            computerWon = true;
            return humanPipsLeft;
        }

    } while (true);
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

void Round::setTrainMarker(int whoseTrain)
{
    if (whoseTrain == 0) {
        //computer train
        this->computerPlayer->setTrainMarker();
    }
    else if (whoseTrain == 1) {
        //human train
        this->humanPlayer->setTrainMarker();
    }
    else if (whoseTrain == 2) {
        //mehicano train
        mexicanTrain.setMarker();
    }
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


bool Round::validateTrainChoice(char userTrain, Tile userTile)
{
    return false;
}

int Round::endRound()
{
    
    return 0;
}

//human won = true, computer won = false
bool Round::getWinner()
{
    if (humanWon) {
        return true;
    }
    return false;//computer won.
}

void Round::cleanData()
{
    //clear boneyard, player hand, computer hand.
    //
    this->computerPlayer->clearData();
    this->humanPlayer->clearData();
    this->m_boneyard.clearHand();
    this->mexicanTrain.clearTrain();
}

void Round::setHand(std::deque<Tile> tiles, int whoseHand)
{
    for (int i = 0; i < tiles.size(); i++) {
        if (whoseHand == 0) {
            //add to computer hand
            computerPlayer->addTileToHand(tiles[i]);
        }
        else if (whoseHand == 1) {
             //add to human hand        
            humanPlayer->addTileToHand(tiles[i]);
        }
        else if (whoseHand == 2) {
            //add to boneyard.
            m_boneyard.addTile(tiles[i]);
        }
    }
}

void Round::setTrain(std::deque<Tile> tiles, int whoseTrain)
{
    //if deque of tiles is empty, then we dont need to add anything so just return
    if (tiles.empty()) {
        return;
    }
    for (int i = 0; i < tiles.size(); i++) {
        //set train values
        if (whoseTrain == 0) {
            //add to computer hand
            computerPlayer->addTileToTrain(tiles[i]);
        }
        else if (whoseTrain == 1) {
            //add to human hand        
            humanPlayer->addTileToTrain(tiles[i]); 
        }
        else if (whoseTrain == 2) {
            //add to boneyard.
            mexicanTrain.addTileBack(tiles[i]);
        }
    }
    //set train end numbers.
    if (whoseTrain == 0) {
        //set computer train end number
        computerPlayer->setTrainEndNumber(tiles.at(tiles.size() - 1).getFirstNumber());
    }
    else if (whoseTrain == 1) {
        //set human train end number        
        humanPlayer->setTrainEndNumber(tiles.at(tiles.size() - 1).getSecondNumber());
    }
    else if (whoseTrain == 2) {
        //set mexican train end number
        mexicanTrain.setTrainEndNumber(tiles.at(tiles.size() - 1).getSecondNumber());
    }
}

char Round::outputMenu(bool humanTurn)
{
    char userInput;
    std::cout << "Save the game (S/s)\n";
    std::cout << "Make a move (M/m)\n";
    if (humanTurn) {
        std::cout << "Ask for help (H/h)\n";
    }
    std::cout << "Quit the game (Q/q)\n\n";
    std::cin >> userInput;
    userInput = tolower(userInput);

    if (userInput == 's') {
        return 's';
    }
    else if (userInput == 'q') {
        exit(1);
    }

    
}

const std::vector<Tile> Round::getHands(int whoseHand)
{
    
    if (whoseHand == 0) {
        //computer hand        

        return this->computerPlayer->getHand();
    }
    else if (whoseHand == 1) {
        //human hand
        return this->humanPlayer->getHand();
    }
    else {
        //boneyard
        return this->m_boneyard.getHand();
    }
}

const std::deque<Tile> Round::getTrains(int whoseTrains)
{
    if (whoseTrains == 0) {
        //computer hand        

        return this->computerPlayer->getTrain();
    }
    else if (whoseTrains == 1) {
        //human hand
        return this->humanPlayer->getTrain();
    }
    else {
        //boneyard
        return this->mexicanTrain.getTrainDeque();
    }
}

int Round::getEngineInt()
{
    return this->engineInt;
}

void Round::setHumanTurn()
{
    this->humanTurn = true;
    this->computerTurn = false;
}

void Round::setComputerTurn()
{
    this->computerTurn = true;
    this->humanTurn = false;
}






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


//g1 culture
//g3 social capital
//g4 negative social ?
//g6 ideology
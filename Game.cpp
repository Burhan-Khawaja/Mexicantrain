#include "Game.h"

int Game::getRoundNumber() {
    return this->roundNumber;
}

void Game::setRoundNumber(int roundNum)
{
    this->roundNumber = roundNum;
}

int Game::getHumanScore() {
    return this->humanScore;
}

void Game::setHumanScore(int hScore)
{
    this->humanScore = hScore;
}

int Game::getComputerScore() {
    return this->computerScore;
}

void Game::setComputerScore(int cScore)
{
    this->computerScore = cScore;
}



void Game::playGame() {
    char userChoice;
    int pipValue = 0;
    do {
        std::cout << "Start new game(s/S), or load game(l/L): ";
        std::cin >> userChoice;
        userChoice = tolower(userChoice);
    } while (userChoice != 's' && userChoice != 'l');


    if (userChoice == 'l') {
        loadGame();
        pipValue = round.startRound(true, this->getHumanScore(),this->getComputerScore(),this->getRoundNumber());
    }
    else {    
        pipValue = round.startRound(false, this->getHumanScore(), this->getComputerScore(), this->getRoundNumber());//start round returns pip value.
    }

    if (pipValue == -10) {
        //user wants to save the game
        saveGame();
    }

    //have to call getWinner function to find ouit which player won.
    if (round.getWinner()) {
        addComputerScore(pipValue);
    }
    else {
        addHumanScore(pipValue);
    }
    playAgainPrompt();
}

void Game::addComputerScore(int pipVal)
{
    this->computerScore += pipVal;
}

void Game::addHumanScore(int pipVal)
{
    this->humanScore += pipVal;
}

void Game::playAgainPrompt()
{
    char userInput;
    do {
        std::cout << "\n\n\n Would you like to play again? (y/Y/n/N)";
        std::cin >> userInput;
        userInput = tolower(userInput);
        if (userInput != 'y' && userInput != 'n') {
            std::cout << "\n\nInvalid input try again.\n\n";
        }
    } while (userInput != 'y' && userInput != 'n');
    if (userInput == 'y') {
        setRoundNumber(this->getRoundNumber() + 1);
        playGame();
    }
    else if (userInput == 'n') {
        outputWinner();
    }
}

void Game::outputWinner()
{
    std::cout << "Your score: ";
    getHumanScore();
    std::cout << "\nComputer Score: ";
    getComputerScore();
    if (getHumanScore() == getComputerScore()) {
        std::cout << "\nThe game is a tie!";
    }
    else if (getHumanScore() > getComputerScore()) {
        std::cout << "\nYou won the game! congratulations";
    }
    else {
        std::cout << "You lost.";
    }
}

void Game::loadGame()
{
    std::string fileName;
    std::cout << "Enter the name of the file you want to load: ";
    std::cin >> fileName;
    std::cout << "loading game: ";
    std::cout << fileName << "\n";
    std::ifstream file(fileName.c_str(), std::ifstream::in);
    std::string singleLine;
    std::deque<Tile> tileDeque;
    //will store whether its the computer or humans turn to load in data from the file.
    bool computerData = false;
    bool humanData = false;
    bool setMarker = false;

    while (std::getline(file, singleLine)) {
        //std::cout << singleLine;
        //const std::string & test;
        tileDeque.clear();    
        bool setMarker = false;
        std::istringstream line(singleLine);
        std::string a1, a2, a3;
        line >> a1;
        if (a1 == "Round:") {
            line >> a2;
            //setround number
            setRoundNumber(stoi(a2));
            continue;
        }        
        if (a1 == "Computer:") {
            computerData = true;
            humanData = false;
            continue;
        }
        if (a1 == "Human:") {
            computerData = false;
            humanData = true;
            //setScoreNumber
            continue;
        }
        if (a1 == "Score:") {
            line >> a2;
            if (computerData) {
                setComputerScore(stoi(a2));
            }
            else {
                setHumanScore(stoi(a2));
            }
            continue;
        }
        if (a1 == "Hand:") {
            tileDeque = parseLineOfTiles(singleLine,setMarker);
            if (computerData) {
                setHand(tileDeque,0);
            }
            else {
                //add tiles to human player hand.
                setHand(tileDeque, 1);
            }
            continue;
        }
        if (a1 == "Train:") {
            tileDeque = parseLineOfTiles(singleLine, setMarker);
            if (computerData) {
                //vector is returned, so if its computer data, then pop it off the front if its computer, back if tis human.
                if (setMarker) {
                    //set computer train marker. Pass in 0 since that represents the computer train
                    round.setTrainMarker(0);
                }
                //back of train contains engine that we dont want to print, so pop it off
                tileDeque.pop_back();
                //have to reverse tileDeque since our train function places the tile to the front
                //and if we did not, the computer train would be backwards/.
                reverse(tileDeque.begin(), tileDeque.end());
                round.setTrain(tileDeque, 0);
                setMarker = false;
            }
            else {//human train
                if (setMarker) {
                    //set human train marker
                    round.setTrainMarker(1);
                }
                
                //the first tile of the human train in the serialization file is the engine tile. get the firs tnumber and set the engine value./
                round.setEngineValue(tileDeque[0].getFirstNumber()); 
                //front of human train contains engine tile that we dont want added to the actual train, so pop it off
                tileDeque.pop_front();
                
                round.setTrain(tileDeque, 1);
            }
            continue;
        }
        if (a1 == "Mexican") {
            computerData = false;
            humanData = false;
            tileDeque = parseLineOfTiles(singleLine, setMarker);
         
            round.setTrain(tileDeque, 2);
        }
        if (a1 == "Boneyard:") {
            tileDeque = parseLineOfTiles(singleLine, setMarker);
            round.setHand(tileDeque, 2);
        }
        if (a1 == "Next") {
            line >> a2 >> a3;
            //a2 should be Player: 
            //a3 contains computer/human.
            if (a3 == "Computer") {
                round.setComputerTurn();
            }
            else {
                round.setHumanTurn();
            }
        }
    }
}

//int whosehand will tell the round class where to add the tiles.
//BURBUR is this function needeD? its just one line.
void Game::setHand(std::deque<Tile> tiles, int whoseHand)
{
    round.setHand(tiles, whoseHand);
}

void Game::saveGame()
{
    std::string saveStateName;
    std::cout << "Enter Save State Name: ";
    std::cin >> saveStateName;
    std::ofstream file;
    file.open(saveStateName);

    file << "Round: ";
    file << getRoundNumber();
    file << "\n\nComputer:";
    file << "\n\tScore: ";
    file << getComputerScore();
    file << "\n\tHand: "; 
    std::vector<Tile> handVector;
    std::deque<Tile> trainDeque;
    handVector = round.getHands(0);
    /*
    for (int i = 0; i < handVector.size(); i++) {
        file << handVector[i].getFirstNumber();
        file << "-";
        file << handVector[i].getSecondNumber();
        file << " ";
    }
    */    
    //convert vector returned when we get the hand to a deque and print it to the file
    std::deque<Tile> computerHandDeque(handVector.begin(), handVector.end());
    printDequeToFile(file, computerHandDeque);
    handVector.clear();
    //print hand to file.
    file << "\n\tTrain: ";
    trainDeque = round.getTrains(0);
    if (round.getComputerTrainMarker()) {
        file << "M ";
    }
    //for (int i = 0; i < trainDeque.size(); i++) {
    //    file << trainDeque[i].getFirstNumber();
    //    file << "-";
    //    file << trainDeque[i].getSecondNumber();
    //    file << " ";
    //}
    printDequeToFile(file, trainDeque);
    trainDeque.clear();
    file << round.getEngineInt() << "-" << round.getEngineInt() << "\n";
    
    //print train to file
    file << "\nHuman:\n\tScore: ";
    file << getHumanScore();
    file << "\n\tHand: ";
    //get human hand
    handVector = round.getHands(1);
    std::deque<Tile> humanHandDeque(handVector.begin(), handVector.end());
    printDequeToFile(file, humanHandDeque);
    handVector.clear();

    file << "\n";
    file << "\tTrain: ";
    trainDeque = round.getTrains(1);
    if (round.getHumanTrainMarker()) {
        file << "M ";
    }
    file << round.getEngineInt() << "-" << round.getEngineInt() << " ";
    printDequeToFile(file, trainDeque);
    trainDeque.clear();
    file << "\n\nMexican Train: ";
    trainDeque = round.getTrains(2);
    printDequeToFile(file, trainDeque);

    //PRINT BONEYARD
    file << "\n\nBoneyard: ";
    handVector = round.getHands(2);
    std::deque<Tile> boneyard(handVector.begin(), handVector.end());
    
    printDequeToFile(file, boneyard);
    


    //BURBUR HAVE TO INCLUDE THE LAST LINE OF THE FILE, WHICH IS WHOSE TURN IT IS.
    file.close();

}

void Game::printDequeToFile(std::ofstream& file, std::deque<Tile>& tiles) {
    for (int i = 0; i < tiles.size(); i++) {
        file << tiles[i].getFirstNumber();
        file << "-";
        file << tiles[i].getSecondNumber();
        file << " ";
    }
    tiles.empty();
}

//parse a line that contains tiles, and return a deque of tiles.
std::deque<Tile> Game::parseLineOfTiles(std::string input, bool& setMarker) {
    std::deque<Tile> tileDeque;
    std::cout << "\n\n\nLine we are dealing with: \n\n";
    std::cout << input;
    std::istringstream line(input);
    std::string firstWord, secondWord;
    //firstWord should contain 'Hand', 'train', 'mexican' which are useless to us since we just need to get tiles and markers/.
    line >> firstWord; 
    std::string  tiles;
    line >> secondWord;
    if (secondWord == "Train:") {
        //mexican train
        //dont need this, do nothing

    }
    else if (secondWord == "M") {
        setMarker = true;
        //have to set marker.
    }
    else {
        //tile value
        int fNum = (int)secondWord[0] - 48;
        int sNum = (int)secondWord[2] - 48;
        tileDeque.push_back(Tile(fNum, sNum));
    }
    while (line >> tiles) {

        if (tiles == "M") {
            //if we parse a "M" in the line, it means that we reached the end of the train and it has a marker on it. 
            //set the marker to true and end the function
            setMarker == true; 
            return tileDeque;
        }
        std::cout << tiles << "\n";
        int fNum = (int)tiles[0] - 48;
        int sNum = (int)tiles[2] - 48;
        tileDeque.push_back(Tile(fNum, sNum));
    }
    return tileDeque;
}

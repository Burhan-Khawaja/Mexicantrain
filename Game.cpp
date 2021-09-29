#include "Game.h"

/* *********************************************************************
Function Name: Game
Purpose: Set default values of Game member variables.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
Game::Game()
{
    this->roundNumber = 0;
    this->humanScore = 0;
    this->computerScore = 0;
    this->round = {};
    this->engineQueue = {};
}

/* *********************************************************************
Function Name: getRoundNumber
Purpose: get what round we are on
Parameters: None
Return Value: integer value that is the round number we are on
Assistance Received: None.
********************************************************************* */
int const Game::getRoundNumber() {
    return this->roundNumber;
}

/* *********************************************************************
Function Name: setRoundNumber
Purpose: set the round number. used for serializationn
Parameters: roundNum, integer that we will set the roundnumber to
Return Value: None
Assistance Received: None.
********************************************************************* */
void Game::setRoundNumber(int roundNum)
{
    this->roundNumber = roundNum;
}

/* *********************************************************************
Function Name: getHumanScore
Purpose: retrieve human score value
Parameters: None
Return Value: integer value that represents the humans score
Assistance Received: None.
********************************************************************* */
int const Game::getHumanScore() {
    return this->humanScore;
}

/* *********************************************************************
Function Name: setHumanScore
Purpose: set the human score value. used in serialization when we load a game in
Parameters: hScore, integer value that is the human score we want to set it to
Return Value: None
Assistance Received: None.
********************************************************************* */
void Game::setHumanScore(int hScore)
{
    this->humanScore = hScore;
}

/* *********************************************************************
Function Name: getComputerScore
Purpose: get computer's score
Parameters: None
Return Value: integer value that is the computers current score
Assistance Received: None.
********************************************************************* */
int Game::getComputerScore() {
    return this->computerScore;
}

/* *********************************************************************
Function Name: setComputerScore
Purpose: set computer's score
Parameters: cScore, integer value that we will set the computer's score to equal.
Return Value: None
Assistance Received: None.
********************************************************************* */
void Game::setComputerScore(int cScore)
{
    this->computerScore = cScore;
}


/* *********************************************************************
Function Name: playGame
Purpose: Start the game, and deal with the outcome of the game
Parameters: None
Return Value: None
Algorithm: 1) Ask if user wants to start a fresh game, or load a game.
           2) If the user wants to load a game, then load the game from whatever file they mention, and start the round.
           3) If the player does not want to load a game, then initialize all the values by default and start the round.
           4) When the user finishes the round, check if the value returned by the round class is -10. If it is, save the game
           5) if the human player won, add the value returned to the computers sore
              5a)else, add the value to the humans score
           6) Prompt the user if they want to play again.
Assistance Received: None.
********************************************************************* */
void Game::playGame() {
    char userChoice;
    int pipValue = 0;
    //1) Ask if user wants to start a fresh game, or load a game.
    do {
        std::cout << "Start new game(s/S), or load game(l/L): ";
        std::cin >> userChoice;
        userChoice = tolower(userChoice);
    } while (userChoice != 's' && userChoice != 'l');

    //2) If the user wants to load a game, then load the game from whatever file they mention, and start the round
    if (userChoice == 'l') {
        loadGame();
        pipValue = round.startRound(true, this->getHumanScore(),this->getComputerScore(),this->getRoundNumber());
    }
    else {  
        //3) If the player does not want to load a game, then initialize all the values by default and start the round.
        //start round returns pip value.
        pipValue = round.startRound(false, this->getHumanScore(), this->getComputerScore(), this->getRoundNumber());
    }
    //4) When the user finishes the turn, check if the value returned by the round class is - 10. If it is, save the game

    if (pipValue == -10) {
        //user wants to save the game
        saveGame();
    }

    if (round.getWinner()) {
        //5) if the human player won, add the value returned to the computers sore
        addComputerScore(pipValue);
    }
    else {
        //5a)else, add the value to the humans score
        addHumanScore(pipValue);
    }
    //6) Prompt the user if they want to play again.
    playAgainPrompt();
}

/* *********************************************************************
Function Name: addComputerScore
Purpose: add to the computer's score
Parameters: pipVal, integer passed by value that is the amount we wish to add the computers score by
Return Value: None
Assistance Received: None.
********************************************************************* */
void Game::addComputerScore(int pipVal)
{
    this->computerScore += pipVal;
}

/* *********************************************************************
Function Name: addHumanScore
Purpose: add to the human's score
Parameters: pipVal, integer passed by value that is the amount we wish to add the human's score by
Return Value: None
Assistance Received: None.
***********(********************************************************* */
void Game::addHumanScore(int pipVal)
{
    this->humanScore += pipVal;
}

/* *********************************************************************
Function Name: playAgainPrompt
Purpose: ask the user if they want to play again, deal with their input
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
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

/* *********************************************************************
Function Name: outputWinner
Purpose: check who won the game, and output the winner
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
void Game::outputWinner()
{
    std::cout << "\n\nYour score: " << std::to_string(getHumanScore());
    std::cout << "\nComputer Score: \n\n" << std::to_string(getComputerScore());
    if (getHumanScore() == getComputerScore()) {
        std::cout << "\nThe game is a tie!";
    }
    else if (getHumanScore() < getComputerScore()) {
        std::cout << "\nYou won the game! congratulations";
    }
    else {
        std::cout << "You lost.";
    }
    std::cout << "\n\n\n\n";
}

/* *********************************************************************
Function Name: loadGame
Purpose: load the game from a file
Parameters: None
Return Value: None
Algorithm:
        1) Ask user for the name of file
        2) Open the file, and begin to read the file line by line
        3) While we read valid lines:
            3a) If the first word we read is round:
                3aa) read in the second word, and set the roud number to that value
            3b) If the first word we read is Computer
                3ba) set the boolean computerData to true, and humanData to false.
            3c) If the first word is Human
                3ca) set the boolean humanData to true, and computerData to false
            3d) If the first word is Score
                3da) if computerData is true, set the computer score to the second word read in
                3db) else set humanData to the 2nd word read in
            3e) If the first word is Hand
                3ea) parse the entire line, and return a deque of all the tiles in the line
                3eb) if computerData is true, add all the tiles to our hand
                3ec) else add the tiles to the human players hand
            3f) If the first word is Train
                3fa) parse the entire line, and return a deque of all the tiles in the line
                3fb) set the trains marker if it needs to be set, and remove the back tile off because it is the engine tile
                3fc) if computer Data is true,
                3fd) reverse the deque
                3fe) add all the tiles to the deque.
                3fg)else if computer data is false, add the tiles to the humans train
            3g) If the first word is Mexican
                3ga) set computer and humandata booleans false
                3gb) parse the line of tiles, and store all the tiles on the line into a deque
                3gc) add the deque of tiles to the mexican train
            3h) If the first word is Boneyard
                3ha) parse the line of tiles, store all the tiles in a deque
                3hb) add the tiles in the deque to the boneyard
            3i) If the first word is Next
                3ia)find the second word. if its computer, set the computers turn to tru
                3ib)else, set the humans turn to true.
Assistance Received: None.
********************************************************************* */
void Game::loadGame()
{
    //get file name that user wants to load
    std::string fileName;
    std::cout << "Enter the name of the file you want to load: ";
    std::cin >> fileName;
    std::cout << "loading game: ";
    std::cout << fileName << "\n";
    //open the file
    std::ifstream file(fileName.c_str(), std::ifstream::in);

    //create a string to store a single line, 
    //create a deque to store the different tiles we have to deal with
    std::string singleLine;
    std::deque<Tile> tileDeque;

    //will store whether its the computer or humans turn to load in data from the file.
    bool computerData = false;
    bool humanData = false;
    bool setMarker = false;

    //while we can read from the file:
    while (std::getline(file, singleLine)) {
        //clear the deque of tiles so we its clean
        tileDeque.clear();    
        bool setMarker = false;
        //read in a line from the file
        std::istringstream line(singleLine);
        std::string a1, a2, a3;
        //read in the first word of the line.
        line >> a1;
        
        //the first word will determine what we do.
        if (a1 == "Round:") {
            line >> a2;
            //set round number
            setRoundNumber(stoi(a2));
            continue;
        }        
        if (a1 == "Computer:") {
            //we are now loading in the computers data
            computerData = true;
            humanData = false;
            continue;
        }
        if (a1 == "Human:") {
            //we are now loading in the humans data
            computerData = false;
            humanData = true;
            continue;
        }
        if (a1 == "Score:") {
            //get the second word on the line, and that is the score.
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
            //parse the line to get all the tiles and then set our hand to whatever the tiles were.
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
            //parse the line to get all the tiles.
            tileDeque = parseLineOfTiles(singleLine, setMarker);
            if (computerData) {
                if (setMarker) {
                    //set computer train marker. Pass in 0 since that represents the computer train
                    round.setTrainMarker(0);
                }
                //back of train contains engine that we dont want to print, so pop it off
                tileDeque.pop_back();
                //have to reverse tileDeque since our train function places the tile to the front
                //and if we did not, the computer train would be backwards.
                reverse(tileDeque.begin(), tileDeque.end());
                //set the computer train.
                round.setTrain(tileDeque, 0);
                setMarker = false;
            }
            else {//human train
                if (setMarker) {
                    //set human train marker
                    round.setTrainMarker(1);
                }
                
                //the first tile of the human train in the serialization file is the engine tile. get the first number and set the engine value.
                round.setEngineValue(tileDeque[0].getFirstNumber()); 
                //front of human train contains engine tile that we dont want added to the actual train, so pop it off
                tileDeque.pop_front();
                
                round.setTrain(tileDeque, 1);
            }
            continue;
        }
        if (a1 == "Mexican") {
            //set mexican train
            computerData = false;
            humanData = false;
            tileDeque = parseLineOfTiles(singleLine, setMarker);
            round.setTrain(tileDeque, 2);
        }
        if (a1 == "Boneyard:") {
            //set boneyard
            tileDeque = parseLineOfTiles(singleLine, setMarker);
            round.setHand(tileDeque, 2);
        }
        if (a1 == "Next") {
            line >> a2 >> a3;
            //a2 should be the word "Player: " 
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

/* *********************************************************************
Function Name: setHand
Purpose: set a players hand to equal a vector passed in. used to load a game from a file
Parameters: tiles - deque of Tiles passed in by value, all Tiles in the deque are added to players hand,
            whoseHand - Integer value that determines where we are adding this deque.
                        0 is computer, 1 is human, 2 is boneyard.
Return Value: None
Algorithm:
            1- For every tile in Tiles
                1a) if whoseHand == 0, add tile to computers hand
                1b) else if whoseHand == 1, add tile to human's hand
                1c) else add tile to boneyard
Assistance Received: None.
********************************************************************* */
void Game::setHand(std::deque<Tile> tiles, int whoseHand)
{
    round.setHand(tiles, whoseHand);
}

/* *********************************************************************
Function Name: saveGame
Purpose: save the gaame to a file
Parameters: None
Return Value: None
Algorithm:
        1) Ask user for name of file to save as
        2) create the save file
        3) write the correct round number to the file
        4) retrieve the hands of the computer, and save it to the file
        5) retrieve the trains of the computer, and save it to the file
        6) repeat step  4 and 5 for human player
        7) print mexican train to file
        8) print boneyuard to the file
        9) print next player to the file
Assistance Received: None.
********************************************************************* */
void Game::saveGame()
{
    //1- ask user for name of file.
    std::string saveStateName;
    std::cout << "Enter Save State Name: ";
    std::cin >> saveStateName;
    std::ofstream file;
    file.open(saveStateName);

    //begin printing out data to the file
    //print round to file
    file << "Round: ";
    file << getRoundNumber();
    file << "\n\nComputer:";
    //print computer score to file
    file << "\n\tScore: ";
    file << getComputerScore();
    file << "\n\tHand: "; 
    std::vector<Tile> handVector;
    std::deque<Tile> trainDeque;
    //get the computer players hand, and store it in handVector.
    handVector = round.getHands(0);
    //convert vector returned when we get the hand to a deque and print it to the file
    std::deque<Tile> computerHandDeque(handVector.begin(), handVector.end());
    printDequeToFile(file, computerHandDeque);
    //clear the vector for next use.
    handVector.clear();
    //print hand to file.
    file << "\n\tTrain: ";
    
    //get values of train, and check if there is a marker on the train.
    trainDeque = round.getTrains(0);
    
    if (round.getComputerTrainMarker()) {
        file << "M ";
    }
    //print train to file.
    printDequeToFile(file, trainDeque);
    //clear deque for next use.
    trainDeque.clear();
    //print engine int after we print the train
    file << round.getEngineInt() << "-" << round.getEngineInt() << "\n";
    
    //HUMANS part of save file, so we repeat what we did above with slight differences.

    file << "\nHuman:\n\tScore: ";
    file << getHumanScore();
    file << "\n\tHand: ";
    //get human hand
    handVector = round.getHands(1);
    std::deque<Tile> humanHandDeque(handVector.begin(), handVector.end());
    //print hand to file
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

    file << "\n\Next Player: ";
    if (round.getHumanTurn()) {
        file << "Human";
    }
    else {
        file << "Computer";
    }
    file.close();
    exit(1);

}

/* *********************************************************************
Function Name: parseLineOfTiles
Purpose: take in an entire line from a file, and create a dequue of Tiles from that line.
Parameters:  file- an ofstream object that is the file we are currently saving the game to. Passed by reference so we are able to change it
                   tiles, Deque of tiles passed by reference so we can add the tiles to the file.
                   This function empties the deque after we have printed them to the file.
Return Value: None
********************************************************************* */
void Game::printDequeToFile(std::ofstream& file, std::deque<Tile>& tiles) {
    for (int i = 0; i < tiles.size(); i++) {
        file << tiles[i].getFirstNumber();
        file << "-";
        file << tiles[i].getSecondNumber();
        file << " ";
    }
    tiles.empty();
}

/* *********************************************************************
Function Name: parseLineOfTiles
Purpose: take in an entire line from a file, and create a dequue of Tiles from that line.
Parameters: input-  string that represents the line from the file.,
            setMarker- boolean value that is passed by value. If we encounter a 'M' character while we parse the line,
                        that means that the train has a marker. and we will set the boolean to true so that we can set the
                        train objects marker to true as well.
Return Value: None
Algorithm:
            1) Read the first word of the line (It will always be useless for us, so we disregard it
            2) Read the second word
                2a) if the second word is Train, do nothing
                2b) else if the second word is "M", set setMarker to true.
                2c) else, get the first and third elements of the word, and create a tile and add it to our list of tile
            3) while we can read in words from the line
                3a) If we read an "M", set the boolean setMarker to true. return the deque of tiles (this will be the last value on the line.
                3b) get the first and third characters from the line, and add them to the deque of tiles.
            4) Return the deque of tiles.
                Assistance Received: None.
********************************************************************* */
std::deque<Tile> Game::parseLineOfTiles(std::string input, bool& setMarker) {
    //tileDeque will store all the tiles from this line

    std::deque<Tile> tileDeque;
    //line stores input in an istringstream object for easier manipulation
    std::istringstream line(input);
    std::string firstWord, secondWord;
    //firstWord should contain 'Hand', 'train', 'mexican' which are useless to us since we just need to get tiles and markers/.
    line >> firstWord; 
    //tiles stores the string representation of the tile
    std::string  tiles;
    //read in the secondword, which is more important
    //if the second word is train, we do nothing.     line >> secondWord;
    if (secondWord == "Train:") {
        //mexican train
        //Dont need to do anything here
    }
    else if (secondWord == "M") {
        //second word is m, set train marker.
        setMarker = true;
        //have to set marker.
    }
    else {
        //else we encountered a tile. create a tile and add it to our deque
        int fNum = (int)secondWord[0] - 48;
        int sNum = (int)secondWord[2] - 48;
        tileDeque.push_back(Tile(fNum, sNum));
    }


    //the rest of the line is a list of tiles, except there may be an 'M' for a marker on the computer train
    while (line >> tiles) {

        if (tiles == "M") {
            //if we parse a "M" in the line, it means that we reached the end of the train and it has a marker on it. 
            //set the marker to true and end the function
            setMarker = true; 
            return tileDeque;
        }
        //create a tile, andadd it to our deque.
        //case the string to an int, and subtract 48 since its in ascii.
        int fNum = (int)tiles[0] - 48;
        int sNum = (int)tiles[2] - 48;
        tileDeque.push_back(Tile(fNum, sNum));
    }
    return tileDeque;
}

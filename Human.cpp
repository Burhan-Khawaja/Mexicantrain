#include "Human.h"
#include <iostream>
#include <string>

Human::Human() {

}

void Human::addTileToHand(Tile tileToAdd)
{
    playerHand.addTile(tileToAdd);
}

void Human::addTileToTrain(Tile tileToAdd) {
    playerTrain.addTileFront(tileToAdd);
}

//BURBUR might have to deletee this
void Human::playedDoubleTile(char userInput, Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard)
{
    ///check for valid move
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

    if (validMove == false) {
        std::cout << "Error, you have no valid move.";
        //function to deal with no valid move should be here.
    }
    //ask for second tile
    std::string userTile2;
    std::cout << "\n\n\nYou have played a double tile. ";
    std::cout << "\n\nYour Hand: \n";
    humanPlayer->printHand();
    std::cout << "\n\nSelect another tile to play: ";
    std::cin >> userTile2;
    if (!verifyTileChoice(userTile2)) {
        //continue;
    }

    Tile userInputAsTile = Tile(userTile2[0] - 48, userTile2[2] - 48);
    if (!hasTile(userInputAsTile)) {
        std::cout << "\n\nError: you do not have that tile. Restarting Move. \n\n\n\n\n";
        //continue;
    }

    //get train they want
    char userTrain;
    std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
    std::cin >> userTrain;
    userTrain = tolower(userTrain);
    //This functions makes surte user enters a valid train, and that it is playable.
    if (!validateTrainChoice(userTrain)) {
        //continue;
    }    

    //user selected another double to play
    if (userInputAsTile.getFirstNumber() == userInputAsTile.getSecondNumber()) {
        //TEMPORARILY remove the tile from the users hand. this way we can see if they have a valid move/a single double left.
        humanPlayer->removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
        //check that if they play another double, their hand is empty.
        //player exhausted hand after playing 2 doubles, ending the game.
        if (humanPlayer->getHandSize() == 1 && playerHand[0].isDouble()) {
            //
        }
        else { //if () {//player can play an additional non-double tile from their hand.
            bool validMove2;
            //BURBUR NEED TO MAKE THIS A SEPERATE FUNCTION INSTEAD OF COPYING/PASTING CODE .,l
            if (this->humanTrainPlayable && playerHasMove(humanPlayer->getTrainEndNumber())) {
                validMove = true;
            }
            if (this->computerTrainPlayable && playerHasMove(computerPlayer->getTrainEndNumber())) {
                validMove = true;
            }
            if (this->mexicanTrainPlayable && playerHasMove(mexicanTrain.getTrainEndNumber())) {
                validMove = true;
            }
            //problem: dont know if the available move is the user playing a double tile.
            //another problem: have to figure out what to do if user selects a different train from the first 2, causing 2 orphan doubles.
        }
    }

    bool validTileSelected = false;
    if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getLastTrainTile())) {
        humanPlayer->addTileToTrain(userInputAsTile);
        validTileSelected = true;
    }
    else if (userTrain == 'c' && tileFitsOnTrain(userInputAsTile, computerPlayer->getLastTrainTile())) {
        computerPlayer->addTileToTrain(userInputAsTile);
        validTileSelected = true;
    }
    else if (userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getLastTile())) {
        //mexican train
        mexicanTrain.addTileBack(userInputAsTile);
        validTileSelected = true;
    }
    if (validTileSelected == false) {
        //continue;
    }

    //user placed tile on different train
    //meaning an orphan double should be created
    if (userTrain != userInput) {
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
    //remove the tile from hand.
}

int Human::play(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard) {
    bool humanTurn = true;
   
    do {
        bool validMove = false;

        if (checkOrphanDoubles(computerPlayer, mexicanTrain) == false) {
            computerTrainPlayable = computerPlayer->getTrainMarker();
            this->humanTrainPlayable = true;
            this->mexicanTrainPlayable = true;
        }

        //check if playera ctually has a valid move.
        //BURBUR THIS SHOULD BE A FUNCTION SINCE ITS USED TWICE/4 times EXACTLY THE SAME WAY
        if (this->humanTrainPlayable && playerHasMove(humanPlayer->getTrainEndNumber())) {
            validMove = true;
        }
        if (this->computerTrainPlayable && playerHasMove(computerPlayer->getTrainEndNumber())) {
            validMove = true;
        }
        if (this->mexicanTrainPlayable && playerHasMove(mexicanTrain.getTrainEndNumber())) {
            validMove = true;
        }

        //remove all tiles from players hand and add 1 unplayable tile for testing reasons.
       
        int tempTestVal = humanPlayer->getHandSize();
        for (int i = 0; i < tempTestVal; i++) {
            humanPlayer->removeTileFromHand(humanPlayer->getFirstHandTile().getFirstNumber(), humanPlayer->getFirstHandTile().getSecondNumber());
        }
        /* //humanPlayer->addTileToHand(Tile(1, 2));
        */
        addTileToHand(Tile(9, 9));
        addTileToHand(Tile(9, 8));

        //user has no move to play
        if (validMove == false) {
            std::cout << "Error: The player does not have a valid move to play. They will draw from the boneyard";
            Tile tmpBoneyardTile;
            if (boneyard.getSize() == 0) {
                tmpBoneyardTile.setValues(-1, -1);
            }
            Tile tmpTile = boneyard.getTile(0);
            boneyard.removeTile(0);
            humanPlayer->addTileToHand(tmpTile);
            if (humanTrainPlayable && playerHasMove(humanPlayer->getTrainEndNumber())) {
                validMove = true;
            }
            if (computerTrainPlayable && playerHasMove(computerPlayer->getTrainEndNumber())) {
                validMove = true;
            }
            if (mexicanTrainPlayable && playerHasMove(mexicanTrain.getTrainEndNumber())) {
                validMove = true;
            }
        }
        std::string userInput;

        std::cout << "Player One's turn to play: \nPlayer One's Hand: \n";
        printHand();
        std::cout << "\nChoose a tile in x-y format to play (ie - 0-0)";
        std::cin >> userInput;

        //BURBUR VERIFTYTILECHOICE AND HAS TILE SHOULD BE IN 1 FUNCITON
        if (!verifyTileChoice(userInput)) {
            continue;
        }
        
        Tile userInputAsTile = Tile(userInput[0] - 48, userInput[2] - 48);
        if (!hasTile(userInputAsTile)) {
            std::cout << "\n\nError: you do not have that tile. Restarting Move. \n\n\n\n\n";
            continue;
        }

         //Tile(userInput[0]-48, userInput[2]-48);

        char userTrain;
        std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
        std::cin >> userTrain;
        userTrain = tolower(userTrain);
        //This functions makes surte user enters a valid train, and that it is playable.
        if (!validateTrainChoice(userTrain)) {
            continue;
        }
        bool validTileSelected = false;
        if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getLastTrainTile())) {
            humanPlayer->addTileToTrain(userInputAsTile);
            validTileSelected = true;
        }
        else if (userTrain == 'c' && tileFitsOnTrain(userInputAsTile, computerPlayer->getLastTrainTile())) {
            computerPlayer->addTileToTrain(userInputAsTile);
            validTileSelected = true;
        }
        else if(userTrain =='m' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getLastTile())) {
            //mexican train
            mexicanTrain.addTileBack(userInputAsTile); 
            validTileSelected = true;
        }
        if (validTileSelected == false) {
            continue;
        }
        removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
        //BURBUR RIGHT HERE CHECK THAT THE PLAYER HAS AN EMPTY HAND AND END THE GAME IF THEY DO.
        if (userInputAsTile.getFirstNumber() != userInputAsTile.getSecondNumber()) {
            humanTurn = false;
        }
        else {
            //user played adouble
            playedDoubleTile(userTrain,  humanPlayer,  computerPlayer,  mexicanTrain,  boneyard);
        }
        
    } while (humanTurn);
    return -1;
}





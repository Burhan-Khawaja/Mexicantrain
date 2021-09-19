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
    if (tileToAdd.getFirstNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToAdd.getSecondNumber());
    }
    else if (tileToAdd.getSecondNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToAdd.getFirstNumber()); 
        tileToAdd.swapNumbers();
    }
    
    playerTrain.addTileBack(tileToAdd);
}

//BURBUR might have to deletee this
void Human::playedDoubleTile(char userInput, Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard)
{
    bool validMoveSelected = false;
    do {
        //check for valid move
        bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);

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
            continue;
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
            continue;
        }

        //user selected another double to play
        if (userInputAsTile.getFirstNumber() == userInputAsTile.getSecondNumber()) {
            //TEMPORARILY? remove the tile from the users hand. this way we can see if they have a valid move/a single double left.
            humanPlayer->removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
            //player exhausted hand after playing 2 doubles, ending the game.  

            if (humanPlayer->getHandSize() == 0) {
                //player hand empty after 2 doubles played. game over.
            }
            //check that if they play another double, their hand is empty.
            //BURBUR might not need this? because of my mistake.
            //above if block deals with user already playing 2 doubles and their hand being over
            //this one im not sure whatit does
            //but the else statemnt should be dealing with the fact that the user has played 2 doubles and now will play a non-double tile from their hand
            if (humanPlayer->getHandSize() == 1 && playerHand[0].isDouble()) {
                //
            }
            else { //if () {//player can play an additional non-double tile from their hand.
                bool validMove2;
                validMove2 = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
                if (validMove2 == false) {
                    std::cout << "\nError: Player does not have a valid move.";

                }
                std::string thirdUserTile;
                std::cout << "Select a Tile to play: ";
                std::cin >> thirdUserTile;
                if (!verifyTileChoice(thirdUserTile)) {
                    continue;
                }

                Tile userInputAsTile3 = Tile(userTile2[0] - 48, userTile2[2] - 48);
                if (!hasTile(userInputAsTile3)) {
                    std::cout << "\n\nError: you do not have that tile. Restarting Move. \n\n\n\n\n";
                    continue;
                }


                //problem: dont know if the available move is the user playing a double tile.
                //another problem: have to figure out what to do if user selects a different train from the first 2, causing 2 orphan doubles.
            }
        }

        bool validTileSelected = false;
        if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getTrainEndNumber())) {
            humanPlayer->addTileToTrain(userInputAsTile);
            validTileSelected = true;
        }
        else if (userTrain == 'c' && tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
            computerPlayer->addTileToTrain(userInputAsTile);
            validTileSelected = true;
        }
        else if (userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
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
        validMoveSelected = true;
    }while (validMoveSelected == false);
}

int Human::play(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard) {
    bool humanTurn = true;
    /*
    //remove all tiles from players hand and add 1 unplayable tile for testing reasons.
    int tempTestVal = humanPlayer->getHandSize();
    for (int i = 0; i < tempTestVal ; i++) {
        humanPlayer->removeTileFromHand(humanPlayer->getFirstHandTile().getFirstNumber(), humanPlayer->getFirstHandTile().getSecondNumber());
    }
    addTileToHand(Tile(9, 5));*/
    do {
        if (checkOrphanDoubles(computerPlayer, mexicanTrain) == false) {
            computerTrainPlayable = computerPlayer->getTrainMarker();
            this->humanTrainPlayable = true;
            this->mexicanTrainPlayable = true;
        }

        bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
        //user has no move to play
        if (validMove == false) {
            bool skipTurn = noPlayableTiles(humanPlayer, computerPlayer, mexicanTrain, boneyard);
            if (skipTurn == false) {//drawn tile is not playable, skip turn after a marker is placed on train.
                humanTurn = false;
                continue;
            }
            else {
                continue;
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
        if (userTrain == 'h' && this->tileFitsOnTrain(userInputAsTile, this->getTrainEndNumber())) {
            humanPlayer->addTileToTrain(userInputAsTile);
            validTileSelected = true;
        }
        else if (userTrain == 'c' && computerPlayer->tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
            computerPlayer->addTileToTrain(userInputAsTile);
            validTileSelected = true;
        }
        else if(userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
            //mexican train
            if (userInputAsTile.getFirstNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(userInputAsTile.getSecondNumber());
            }
            else if (userInputAsTile.getSecondNumber() == mexicanTrain.getTrainEndNumber()) {
                mexicanTrain.setTrainEndNumber(userInputAsTile.getFirstNumber());
                userInputAsTile.swapNumbers();
            }
            mexicanTrain.addTileBack(userInputAsTile); 
            validTileSelected = true;
        }
        if (validTileSelected == false) {
            continue;
        }
        removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
        //BURBUR RIGHT HERE CHECK THAT THE PLAYER HAS AN EMPTY HAND AND END THE GAME IF THEY DO.
        if (humanPlayer->getHandSize() == 0) {
            std::cout << "\n\nYou Won! your hand is empty.";
            int cpuPips = computerPlayer->sumOfPips();
            return cpuPips;
        }
        if (userInputAsTile.getFirstNumber() != userInputAsTile.getSecondNumber()) {
            humanTurn = false;
        }
        else {
            //user played adouble
            playedDoubleTile(userTrain,  humanPlayer,  computerPlayer,  mexicanTrain,  boneyard);
        }
        
    } while (humanTurn);
    return 0;
}





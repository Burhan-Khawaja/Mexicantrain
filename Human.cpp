#include "Human.h"
#include <iostream>
#include <string>

Human::Human() {
    this->playerTrain = {};
    this->playerHand = {};
    this->trainLastNumber = -1;
    //these 3 booleans dictate weather the player can play on each train.
    this->humanTrainPlayable = false;
    this->computerTrainPlayable = false;
    this->mexicanTrainPlayable = false;
}


void Human::addTileToTrain(Tile tileToAdd) {

    playerTrain.addTileBack(tileToAdd);
}

void Human::playedDoubleTile(char userInput, Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard)
{
    bool validMoveSelected = false;
    do {
        //check for valid move
        bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);

        if (validMove == false) {
            std::cout << "Error, you have no valid move.";
            bool canPlayTile = humanPlayer->noPlayableTiles( humanPlayer,  computerPlayer,  mexicanTrain, boneyard);
            if (canPlayTile) {
                continue;
            }
            else {
                //BURBUR CHECK IF BONEYARD IS EMPTY DEAL WITH THIS if ();
            }
            return;
        }
        //ask for second tile
        std::string userTile2;
        std::cout << "\n\n\nYou have played a double tile. \n";

        Tile userInputAsTile = playerTileChoice();
        if (userInputAsTile.getFirstNumber() == -1 && userInputAsTile.getSecondNumber() == -1) {
            std::cout << "Select a different tile to play.\n\n";
            continue;
        }

        //get train they want
        char userTrain;
        std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
        std::cin >> userTrain;
        userTrain = tolower(userTrain);
        //This functions makes surte user enters a valid train, and that it is playable.
        if (!validateTrainChoice(userTrain)) {
            std::cout << "\nRestarting move. Select another tile to play.";
            continue;
        }

        bool validTileSelected = false;
        //this variable is included for output reasons so we can reiterate to the user what train they played on.
        std::string trainSelected;
        if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getTrainEndNumber())) {
            humanPlayer->addTileToTrain(userInputAsTile);
            if (humanPlayer->getOrphanDouble()) {
                humanPlayer->resetOrphanDouble();
            }
            validTileSelected = true;
            trainSelected = "human";
        }
        else if (userTrain == 'c' && tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
            computerPlayer->addTileToTrain(userInputAsTile);
            if (computerPlayer->getOrphanDouble()) {
                computerPlayer->resetOrphanDouble();
            }
            validTileSelected = true;
            trainSelected = "computer";
        }
        else if (userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
            //mexican train
            trainSelected = "mexican";
            mexicanTrain.addTileBack(userInputAsTile);
            if (mexicanTrain.getOrphanDouble()) {
                mexicanTrain.resetOrphanDouble();
            }
            validTileSelected = true;
        }
        if (validTileSelected == false) {
            continue;
        }
        
        std::cout << "You have played ";
        userInputAsTile.printTile();
        std::cout << " On the " << trainSelected << " train.";

        //user selected another double to play
        if (userInputAsTile.getFirstNumber() == userInputAsTile.getSecondNumber()) {
            std::cout << "\n\nThe second tile you have also played is another double!\nYou are allowed to play a follow up non double tile.";
            //TEMPORARILY? remove the tile from the users hand. this way we can see if they have a valid move/a single double left.
            humanPlayer->removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
           
            //player exhausted hand after playing 2 doubles, ending the game.  
            if (humanPlayer->getHandSize() == 0) {
                //player hand empty after 2 doubles played. game over.
                return;
            }
            //check that if they play another double, their hand is empty.
            //BURBUR might not need this? because of my mistake.
            //above if block deals with user already playing 2 doubles and their hand being over
            //this one im not sure whatit does
            //but the else statemnt should be dealing with the fact that the user has played 2 doubles and now will play a non-double tile from their hand
            if (humanPlayer->getHandSize() == 1 && playerHand[0].isDouble()) {
                //not allowed to play 3 doubles, only 2 doubles and a non double so this should be banned somehow.

            }
            else { //if () {//player can play an additional non-double tile from their hand.
                bool validMove2;
                validMove2 = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
                if (validMove2 == false) {
                    std::cout << "\nError: Player does not have a valid move.\n";
                    std::cout << "You are not allowed to play 2 doubles and not have an empty hand or have a third non double follow up. Select a different tile.";
                    humanPlayer->addTileToHand(Tile(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber())); 
                    continue;
                    //break loop, add doulbe tile back to hand, and start over.
                }
                Tile userInputAsTile3;
                userInputAsTile3 = playerTileChoice();
                /*
                std::cout << "Select a Tile to play: ";
                std::cin >> thirdUserTile;
                if (!verifyTileChoice(thirdUserTile)) {
                    continue;
                }

                 = Tile(userTile2[0] - 48, userTile2[2] - 48);
                
                if (!hasTile(userInputAsTile3)) {
                    std::cout << "\n\nError: you do not have that tile. Restarting Move. \n\n\n\n\n";
                    continue;
                }
*/
                if (userInputAsTile3.getFirstNumber() == userInputAsTile3.getSecondNumber()) {
                    std::cout << "Error: You are not allowed to play 3 double tiles in a single turn. Restarting move.";
                    humanPlayer->addTileToHand(Tile(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber()));
                    continue;
                }

                //get train they want
                char userTrain;
                std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
                std::cin >> userTrain;
                userTrain = tolower(userTrain);
                //This functions makes surte user enters a valid train, and that it is playable.
                if (!validateTrainChoice(userTrain)) {
                    std::cout << "\nRestarting move. Select another tile to play.";
                    continue;
                }

                bool validTileSelected = false;
                if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getTrainEndNumber())) {
                    humanPlayer->addTileToTrain(userInputAsTile);
                    if (humanPlayer->getOrphanDouble()) {
                        humanPlayer->resetOrphanDouble();
                    }
                    trainSelected = "human";
                    validTileSelected = true;
                }
                else if (userTrain == 'c' && tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
                    computerPlayer->addTileToTrain(userInputAsTile);
                    if (computerPlayer->getOrphanDouble()) {
                        computerPlayer->resetOrphanDouble();
                    }
                    validTileSelected = true;
                    trainSelected = "computer";
                }
                else if (userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
                    //mexican train
                    mexicanTrain.addTileBack(userInputAsTile);
                    if (mexicanTrain.getOrphanDouble()) {
                        mexicanTrain.resetOrphanDouble();
                    }
                    trainSelected = "mexican";
                    validTileSelected = true;
                }
                if (validTileSelected == false) {
                    continue;
                }
                std::cout << "\nYou placed a third tile, ";
                userInputAsTile3.printTile();
                std::cout << " on the " << trainSelected << " train.\n";
                removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
                removeTileFromHand(userInputAsTile3.getFirstNumber(), userInputAsTile3.getSecondNumber());
                //BURBUR CHECK FOR ORPHAN DOUBLES 2 OF THEM.
                return;
            }
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
        removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
        validMoveSelected = true;
    }while (validMoveSelected == false);
}

int Human::play(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engine) {
    bool humanTurn = true;
    this->printGameState(humanPlayer, computerPlayer, mexicanTrain, boneyard, humanScore, computerScore, roundNumber, engine);

    do {
        if (checkOrphanDoubles(humanPlayer, computerPlayer, mexicanTrain) == false) {
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

        std::cout << "Player One's turn to play: \n";
        //printHand();
        Tile userInputAsTile = playerTileChoice();
        if (userInputAsTile.getFirstNumber() == -1 && userInputAsTile.getSecondNumber() == -1) {
            continue;
        }
        /*
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
*/
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
            if (humanPlayer->getOrphanDouble()) {
                humanPlayer->resetOrphanDouble();
            }
            validTileSelected = true;
        }
        else if (userTrain == 'c' && computerPlayer->tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
            computerPlayer->addTileToTrain(userInputAsTile);
            if (computerPlayer->getOrphanDouble()) {
                computerPlayer->resetOrphanDouble();
            }
            validTileSelected = true;
        }
        else if(userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
            mexicanTrain.addTileBack(userInputAsTile); 
            if (mexicanTrain.getOrphanDouble()) {
                mexicanTrain.resetOrphanDouble();
            }
            validTileSelected = true;
        }

        if (validTileSelected == false) {
            continue;
        }
        removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
        //BURBUR RIGHT HERE CHECK THAT THE PLAYER HAS AN EMPTY HAND AND END THE GAME IF THEY DO.

        
        //user played adouble
        if (userInputAsTile.getFirstNumber() == userInputAsTile.getSecondNumber()) {
            playedDoubleTile(userTrain, humanPlayer, computerPlayer, mexicanTrain, boneyard);
        }

        if (humanPlayer->getHandSize() == 0) {
            std::cout << "\n\nYou Won! your hand is empty.";
            int cpuPips = computerPlayer->sumOfPips();
            return cpuPips;
        }
        humanTurn = false;
    } while (humanTurn);
   
    return 0;
}
   





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
void Human::playedDoubleTile(std::string userInput)
{

}


int Human::play(Player* humanPlayer, Player* computerPlayer, Train mexicanTrain, Hand boneyard) {
    bool humanTurn = true;
   
    do {
        bool validMove = false;
        
        if (checkOrphanDoubles(computerPlayer, mexicanTrain) == false) {
            computerTrainPlayable = computerPlayer->getTrainMarker();
            humanTrainPlayable = true;
        }

        //check if playeractually has a valid move.
        //BURBUR THIS SHOULD BE A FUNCTION SINCE ITS USED TWICE EXACTLY THE SAME WAY
        if (humanTrainPlayable && playerHasMove(humanPlayer->getTrainEndNumber())) {
            validMove = true;
        }
        if (computerTrainPlayable && playerHasMove(computerPlayer->getTrainEndNumber())) {
            validMove = true;
        }
        if (mexicanTrainPlayable && playerHasMove(mexicanTrain.getTrainEndNumber())) {
            validMove = true;
        }

        //remove all tiles from players hand and add 1 unplayable tile for testing reasons.
        for (int i = 0; i < humanPlayer->getHandSize(); i++) {
            humanPlayer->removeTileFromHand(humanPlayer->getFirstHandTile().getFirstNumber(), humanPlayer->getFirstHandTile().getSecondNumber());
        }
        humanPlayer->addTileToHand(Tile(1, 2));
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
        addTileToHand(Tile(9, 9));
        std::string userInput;
        
        std::cout << "Player One's turn to play: \nPlayer One's Hand: \n";
        printHand();
        std::cout << "\nChoose a tile in x-y format to play (ie - 0-0)";
        std::cin >> userInput;
       
        if (!verifyTileChoice(userInput)) {
            continue;
        }
        Tile userInputAsTile = Tile(userInput[0] -48, userInput[2]-48);
        //various testing code wil between this comment and the next one.
        //computerPlayer.setOrphanDouble();//human train should be unplayable.
        //computerPlayer.setOrphanDouble();
        //computerPlayer.resetOrphanDouble();

        //end of testing code

         //Tile(userInput[0]-48, userInput[2]-48);

        char userTrain;
        std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
        std::cin >> userTrain;
        userTrain = tolower(userTrain);
        if (!validateTrainChoice(userTrain)) {
            continue;
        }

        if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getLastTrainTile())) {
            humanPlayer->addTileToTrain(userInputAsTile);
        }
        /*
        

        if (userTrain == 'h' && getHumanTrainPlayable()) {
            if (humanPlayer.tileFitsOnTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48), engineInt, humanPlayer.getFirstTrainTile()) == false) {
                std::cout << "Error: the tile you entered: " << userInput << " is not a valid tile since it does not fit on the human train.\n";
                continue;
            }
            humanPlayer.addTileToTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48));
        }
        else if (userTrain == 'c' && getComputerTrainPlayable()) {
            if (computerPlayer.tileFitsOnTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48), engineInt, computerPlayer.getLastTrainTile()) == false) {
                std::cout << "Error: the tile you entered: " << userInput << " is not a valid tile.\n";
                continue;
            }
            computerPlayer.addTileToTrain(Tile((int)userInput[0] - 48, (int)userInput[2] - 48));
        }
        else if (userTrain == 'm' && getMexicanTrainPlayable()) {
            std::cout << "Mexican train not implemented yet jeez. will ad later";
            if (mexicanTrain.isEmpty()) {

            }
        }
        else {
            std::cout << "Error: invalid train selected.";
            continue;
        }
        humanPlayer.removeTileFromHand((int)userInput[0] - 48, (int)userInput[2] - 48);
        //BURBUR have to make sure player has tile,

        //double check. If the player doesnt play a double, then their turn is over.
        if (userInput[0] == userInput[2]) {
            //humanPlayer.playedDoubleTile(userInput);
            playedDoubleTile(userInput);
        }
*/
        if (userInputAsTile.getFirstNumber() != userInputAsTile.getSecondNumber()) {
            humanTurn = false;
        }
        else {
            //user played adouble
            //playedDoubleTile();
        }
        removeTileFromHand(userInputAsTile.getFirstNumber(),userInputAsTile.getSecondNumber());
    } while (humanTurn);
    return -1;
}





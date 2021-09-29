#pragma once
#include "Computer.h"

/* *********************************************************************
Function Name: Computer
Purpose: Set default values of Computer member variables.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
Computer::Computer() {
    this->playerTrain = {};
    this->playerHand = {};
    this->trainLastNumber = -1;
    humanTrainPlayable = false;
    computerTrainPlayable = false;
    mexicanTrainPlayable = false;
}

/* *********************************************************************
Function Name: addTileToTrain
Purpose: add a tile to the train. The computer will add the tile to the front of the train
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
void Computer::addTileToTrain(Tile tileToAdd) {
    if (tileToAdd.getFirstNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToAdd.getSecondNumber());
        tileToAdd.swapNumbers();
    }
    else if (tileToAdd.getSecondNumber() == playerTrain.getTrainEndNumber()) {
        playerTrain.setTrainEndNumber(tileToAdd.getFirstNumber());
    }
    playerTrain.addTileFront(tileToAdd);
}

/* *********************************************************************
Function Name: play
Purpose: This function will handle the steps and rules for when a computer player plays a turn
Parameters:
    Player * humanPlayer - Stores all the information for the human player.
                           Passed so we can manipulate and access its member variables if needed (ie- its train). passed by reference
    Player * computerPlayer - Stores all information of the computer player.
                            passed into the function so we can manipulate and access its member variables. passed by reference
    Train& mexicanTrain - Train object that is passed by reference. This train will be changed when a user plays a tile on the mexican train.
    Hand& boneyard - Hand object passed by reference. Passed in so a player can take a tile if they do not have any playable tiles.
    int humanScore - humanScore, passed in so we can print it to the console for the user to see before their turns.
    int computerScore - computerScore, integer passed in so we can print it for  the user to see before their turns
    int roundNumber- integer that represents the round number so we can print it out for the user to see before their turn.
    int engine - this integer represets the engine value. we pass it in so when we print the game state, we can print out the engine.
Return Value: Integer value that represents the pips of the human players hand if the computer wins,
              -10 if the player wants to save the game
              -666 if the player passes their turn and the boneyard is empty.
Algorithm:
        1) Check if any orphan doubles exist.
            1a) If they do, set the orphan trains as the only playable trains
            1b) If there are no orphan trains, then check if the human train has a marker, and set the human train playable if it does
            1c) Set computer and mexican train playable
        2) Check if the computer player has a valid move.
            2a) If they do not have a valid move, make them draw a tile. if its playable, play it, else mark their train and skip their turn
        3) Find the best move for the computer to play
            3a)Find any available doubles to play
            3b)Find any single tile to play if there are no doubles
            3c)repead steps 3a and 3b until you play 3 tiles (2 doubles and a non double), or you play a non double tile
        4) print out the reasoning for why the user played the move it did.
        5) Play all the tiles on their respective train
            5a) If the computer train has a marker on it, clear the marker
            5b) For every train, check if it has an orphan double. If it does, clear the orphan double.
        6) check if we created any orphan doubles with our moves. Set the trains as orphans if we have.
        7) Return from the function.

Assistance Received: None.
********************************************************************* */
int Computer::play(Player * humanPlayer, Player * computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engine) {
    
    this->printGameState(humanPlayer, computerPlayer, mexicanTrain, boneyard, humanScore, computerScore, roundNumber, engine);

    //tilesToPlay and trainsToPlayOn will later hold the best tiles the computer can play, and the corresponding trains to play them on.
    std::vector<Tile> tilesToPlay;
    std::vector<char> trainsToPlayOn;
    
    // 1)check for any orphan doubles.
    if (checkOrphanDoubles(humanPlayer,computerPlayer, mexicanTrain) == false) {
        //1b) If there are no orphan trains, then check if the human train has a marker, and set the human train playable if it does
        humanTrainPlayable = humanPlayer->getTrainMarker();
        this->computerTrainPlayable = true;
        this->mexicanTrainPlayable = true;
    }

    //2) Check if the computer player has a valid move.
    bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);

    //2a) If they do not have a valid move, make them draw a tile. if its playable, play it, else mark their train and skip their turn
    if (!validMove) {
        bool skipTurn = noPlayableTiles(humanPlayer, computerPlayer, mexicanTrain, boneyard);
        if (skipTurn == false) {
            //drawn tile is not playable, skip turn after a marker is placed on train.
            this->setTrainMarker();
            if (boneyard.getSize() == 0) {
                //if boneyard is empty, and have to skip turn return -666 since thats our error code for this scenario
                return -666;
            }

            return 0;
        }
    }

    //find the best move that the computer can make.
    findBestMove(humanPlayer, computerPlayer, mexicanTrain, boneyard, tilesToPlay, trainsToPlayOn);
    //interpretBestMove will print out the explination for why the tiles and trains were chosen.
    interpretBestMove(tilesToPlay, trainsToPlayOn);
    //begin  adding the tiles to the trains.
    if (!tilesToPlay.empty()) {
        for (int i = 0; i < tilesToPlay.size(); i++) {
            if (trainsToPlayOn[i] == 'c') {
                //add the tiles to the computer train.
                computerPlayer->addTileToTrain(tilesToPlay[i]);
                //check the computer train for a marker, and clear it if there is one
                if (computerPlayer->getTrainMarker()) {
                    computerPlayer->resetTrainMarker();
                }
                //also check for an orphan double and clear it if it exists.
                if (computerPlayer->getOrphanDouble()) {
                    computerPlayer->resetOrphanDouble();
                }
            }
            else if (trainsToPlayOn[i] == 'h') {
                humanPlayer->addTileToTrain(tilesToPlay[i]);
                //add the tile to the human train, and check for an orphan double.
                if (humanPlayer->getOrphanDouble()) {
                    humanPlayer->resetOrphanDouble();
                }
            }
            else {
                //add tile to the mexican train, and check for an orphan double. 
                mexicanTrain.addTileBack(tilesToPlay[i]);
                if (mexicanTrain.getOrphanDouble()) {
                    mexicanTrain.resetOrphanDouble();
                }
            }
            //remove the tile from the players hand.
            computerPlayer->removeTileFromHand(tilesToPlay[i].getFirstNumber(), tilesToPlay[i].getSecondNumber());
            //check if the computer's hand is empty, meaning tey won the game
            if (computerPlayer->getHandSize() == 0) {
                //checkGameWon returns pips of human player.
                return checkGameWon(humanPlayer);
            }
        }
    }
    //output the reasoning for the players move
    std::cout <<"\n\n" << interpretBestMove(tilesToPlay, trainsToPlayOn);
    //user played 2 tiles, so theres a chance that there is 1 orphan double.
    if (trainsToPlayOn.size() >= 2) {
        if (trainsToPlayOn[0] != trainsToPlayOn[1]) {
            //train user played on arent equal to each other, so make the first train an orphan double
            if (trainsToPlayOn[0] == 'm') {
                mexicanTrain.setOrphanDouble();
            }
            else if (trainsToPlayOn[0] == 'c') {
                computerPlayer->setOrphanDouble();
            }
            else {
                humanPlayer->setOrphanDouble();
            }
        }
    }
    //user played 3 tiles, so we check if the second tile they played is also an orphan double.
    if (trainsToPlayOn.size() == 3) {
        if (trainsToPlayOn[1] != trainsToPlayOn[2]) {
            //train user played on arent equal to each other, so make the first train an orphan double
            if (trainsToPlayOn[1] == 'm') {
                mexicanTrain.setOrphanDouble();
            }
            else if (trainsToPlayOn[1] == 'c') {
                computerPlayer->setOrphanDouble();
            }
            else {
                humanPlayer->setOrphanDouble();
            }
        }

    }
    tilesToPlay.clear();
    trainsToPlayOn.clear();
    return -1;


}

/* *********************************************************************
Function Name: checkGameWon
Purpose: Check if the computer player won the game. Also return the human's pips left.
Parameters: humanPlayer- player object pointer passed by reference. Needed so we can calculate the pips left in the players hand.
Return Value: integer value that represents the pips left in the loser's hand
Assistance Received: None.
********************************************************************* */
int Computer::checkGameWon(Player * humanPlayer)
{
    if (this->getHandSize() == 0) {
        std::cout << "\n\n\nyou lost! the computer won.\n\n\n";
        return humanPlayer->sumOfPips();
    }
}

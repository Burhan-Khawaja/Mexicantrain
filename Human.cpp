#include "Human.h"
#include <iostream>
#include <string>


/* *********************************************************************
Function Name: Human
Purpose: Set default values of Human member variables.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
Human::Human() {
    this->playerTrain = {};
    this->playerHand = {};
    this->trainLastNumber = -1;
    //these 3 booleans dictate weather the player can play on each train.
    this->humanTrainPlayable = false;
    this->computerTrainPlayable = false;
    this->mexicanTrainPlayable = false;
}

/* *********************************************************************
Function Name: addTileToTrain
Purpose: add a tile to the players train.
Parameters: tileToAdd, Tile passed by value that will be added to the back of the train
Return Value: None
Assistance Received: None.
********************************************************************* */
void Human::addTileToTrain(Tile tileToAdd) {

    playerTrain.addTileBack(tileToAdd);
}

/* *********************************************************************
Function Name: playedDoubleTile
Purpose: Deal with ruleset when a human player plays a double tile
Parameters: userInput- Char value that we use to check if the other trains the user play on are different, meaning they made an orphan double
            humanPlayer- pointer to a Player object that we need to access the human players
            computerPlayer- pointer to a computer player object that we need to access the computer players trains
            mexicanTrain- Train object that stores the mexican train
                          needed so we can play on the mexican train and get its information. passed by reference since we might play on it
            boneyard- Hand passed by refernce that contains the boneyard.
                      passed since the player might not have a move at some point and has to draw from the boneyard.
Return Value: None
Algorithm:
            1) Check if the user has a valid move
                1a) if they do not, make them draw a tile
                    1aa) if the drawn tile is playable, play it, otherwise add a marker to their train and skip turn
            2) Ask the user for what tile they want to play. Verify that it is an accurate tile that exists in their hand
            3) Ask the user what train they want to play it on, and make sure they enter a valid train
            4) Check that the train and tile the user chose matches, and fits.
                4a)If the tile doesnt fit on the train, go to step 2
            5)If the second tile the user played was a double:
                5a)Check if their hand is empty. If it is, return from this function and end the game.
                5b)Check if the user has a valid move after playing the second double.
                    5ba)If they do not have a valid move, then add the 2nd tile they played back into their hand and goto step 2
                5c)else, ask the user to play an additional non double follow up tile. verify their input
                5d)If the third tile the user played is a third double, restart the move from step 2 b/c they cant play 3 doubles.
                5e)ask the user for what train they want to play on. Verify its input
                5f)verify the tile fits on the train and remove both tiles from the players hand if they played 2 tiles, and return from the function
            6)check for orphan doubles. If the second train the user entered does not equal the first train, make the first one an orphan double
            7)remove the first tile from the players hand
            8)return

Assistance Received: None.
********************************************************************* */
void Human::playedDoubleTile(char userInput, Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard)
{
    bool validMoveSelected = false;
    do {
        //1) Check if the user has a valid move
        bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);

        if (validMove == false) {
            //1a) if they do not, make them draw a tile
            std::cout << "Error, you have no valid move.";
            bool canPlayTile = humanPlayer->noPlayableTiles( humanPlayer,  computerPlayer,  mexicanTrain, boneyard);
            if (canPlayTile) {
                //1aa) if the drawn tile is playable, play it, otherwise add a marker to their train and skip turn
                continue;
            }
            else {
            }
            return;
        }
        //2) Ask the user for what tile they want to play. Verify that it is an accurate tile that exists in their hand
        std::string userTile2;
        std::cout << "\n\n\nYou have played a double tile. \n";

        Tile userInputAsTile = playerTileChoice();
        if (userInputAsTile.getFirstNumber() == -1 && userInputAsTile.getSecondNumber() == -1) {
            std::cout << "Select a different tile to play.\n\n";
            continue;
        }

        //3) Ask the user what train they want to play it on, and make sure they enter a valid train

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

        //4) Check that the train and tile the user chose matches, and fits.
        if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getTrainEndNumber())) {
            humanPlayer->addTileToTrain(userInputAsTile);
            //after adding the tile to the train, check if there is an orphan double
            //if there is, clear the orphan double
            if (humanPlayer->getOrphanDouble()) {
                humanPlayer->resetOrphanDouble();
            }
            validTileSelected = true;
            trainSelected = "human";
        }
        else if (userTrain == 'c' && tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
            computerPlayer->addTileToTrain(userInputAsTile);
            //check for orphan double, clear it if there is
            if (computerPlayer->getOrphanDouble()) {
                computerPlayer->resetOrphanDouble();
            }
            validTileSelected = true;
            trainSelected = "computer";
        }
        else if (userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
            //check for orphan double and clear it if there is.
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

        //5)If the second tile the user played was a double:
        if (userInputAsTile.getFirstNumber() == userInputAsTile.getSecondNumber()) {
            std::cout << "\n\nThe second tile you have also played is another double!\nYou are allowed to play a follow up non double tile.";
            // remove the tile from the users hand. this way we can see if they have a valid move/a single double left.
            humanPlayer->removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
           
            //player exhausted hand after playing 2 doubles, ending the game.  
            if (humanPlayer->getHandSize() == 0) {
                //player hand empty after 2 doubles played. game over.
                return;
            }

            //check that if they play another double, their hand is empty.
            if (humanPlayer->getHandSize() == 1 && playerHand[0].isDouble()) {
                //not allowed to play 3 doubles, only 2 doubles and a non double.

            }
            else { 
                //player can play an additional non-double tile from their hand.
                bool validMove2;
                validMove2 = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
                //check that user actually has a move after playing 2 doubles. they are not allowed to play 2 dbls and not have a third tile
                if (validMove2 == false) {
                    std::cout << "\nError: Player does not have a valid move.\n";
                    std::cout << "You are not allowed to play 2 doubles and not have an empty hand or have a third non double follow up. Select a different tile.";
                    //add the tile back to their hand, restart move.
                    humanPlayer->addTileToHand(Tile(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber())); 
                    continue;
                }
                //5c)else, ask the user to play an additional non double follow up tile. verify their input
                Tile userInputAsTile3;
                userInputAsTile3 = playerTileChoice();
                if (userInputAsTile3.getFirstNumber() == userInputAsTile3.getSecondNumber()) {
                    std::cout << "Error: You are not allowed to play 3 double tiles in a single turn. Restarting move.";
                    humanPlayer->addTileToHand(Tile(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber()));
                    continue;
                }

                //ask the user for what train they want to play on. Verify its input
                char userTrain;
                std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
                std::cin >> userTrain;
                userTrain = tolower(userTrain);

                //This functions makes sure user enters a valid train, and that it is playable.
                if (!validateTrainChoice(userTrain)) {
                    std::cout << "\nRestarting move. Select another tile to play.";
                    continue;
                }

                bool validTileSelected = false;
                //add the tile to the train after verifying it fits on the train
                if (userTrain == 'h' && tileFitsOnTrain(userInputAsTile, this->getTrainEndNumber())) {
                    humanPlayer->addTileToTrain(userInputAsTile);
                    //check for ophan double ,clear if it exists
                    if (humanPlayer->getOrphanDouble()) {
                        humanPlayer->resetOrphanDouble();
                    }
                    trainSelected = "human";
                    validTileSelected = true;
                }
                else if (userTrain == 'c' && tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
                    computerPlayer->addTileToTrain(userInputAsTile);
                    //add tile, clear orphan double if it exists
                    if (computerPlayer->getOrphanDouble()) {
                        computerPlayer->resetOrphanDouble();
                    }
                    validTileSelected = true;
                    trainSelected = "computer";
                }
                else if (userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
                    //add tile, clear orphan double if it exists
                    mexicanTrain.addTileBack(userInputAsTile);
                    if (mexicanTrain.getOrphanDouble()) {
                        mexicanTrain.resetOrphanDouble();
                    }
                    trainSelected = "mexican";
                    validTileSelected = true;
                }

                //if user entered invalid tile, restart move.
                if (validTileSelected == false) {
                    continue;
                }

                std::cout << "\nYou placed a third tile, ";
                userInputAsTile3.printTile();
                std::cout << " on the " << trainSelected << " train.\n";
                //remove both tiles from players hand
                removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());
                removeTileFromHand(userInputAsTile3.getFirstNumber(), userInputAsTile3.getSecondNumber());
                return;
            }
        }

        //check if user placed tile on different train
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


/* *********************************************************************
Function Name: play
Purpose: deal with the proper procedure for human players move
Parameters:
    humanPlayer - pointer to a Player object. Stores all the information for the human player.
                           Passed so we can manipulate and access its member variables if needed (ie- its train). passed by reference
    computerPlayer - pointer to a computer object. Stores all information of the computer player.
                            passed into the function so we can manipulate and access its member variables. passed by reference
    mexicanTrain - Pointer to a train object that is passed by reference. This train will be changed when a user plays a tile on the mexican train.
    boneyard - Hand object passed by reference. Passed in so a player can take a tile if they do not have any playable tiles.
    humanScore - integer that represents humanScore, passed in so we can print it to the console for the user to see before their turns.
    computerScore - represents the computer Score, integer passed in so we can print it for the user to see before their turns
    roundNumber- integer that represents the round number so we can print it out for the user to see before their turn.
    engine - this integer represets the engine value. we pass it in so when we print the game state, we can print out the engine.
Return Value: Integer value that represents the pips of the computer players hand if the computer wins,
              -10 if the player wants to save the game
              -666 if the player passes their turn and the boneyard is empty.
Algorithm:
        1) Check if any orphan doubles exist.
            1a) If they do, set the orphan trains as the only playable trains
            1b) If there are no orphan trains, then check if the human train has a marker, and set the human train playable if it does
            1c) Set computer and mexican train playable
        2) Check if the computer player has a valid move.
            2a) If they do not have a valid move, make them draw a tile. if its playable, play it, else mark their train and skip their turn
        3) Ask the user to enter a tile
            3a) Store the tile in userInputAsTile, and verify that the user entered a correct value for the tile, and that it exists within their hand
        4) Ask the user for a train to play on
            4a) check that the train they entered is a valid train and is playable.
        5) Check that the tile the user played on fits on the train they chose to play on.
            5a) If it does, add the tile to the train. For the human train, check if there is a marker on it
                5aa)If there is a marker on the train and the human played on it, clear the marker
            5b) check the train the user played on for an orphan double.
                5ba)If there is an orphan double on the train played on, clear it.
        6)remove the tile from the players hand
        7)check that the players hand is empty.
            7a)If the players hand is empty, end the game by returning the value of the computers pips in their hand
        8)If the user played a double, call the playedDoubleTile function that will ask the user for follow up tiles.
        9)End the turn.
********************************************************************* */

int Human::play(Player* humanPlayer, Player* computerPlayer, Train& mexicanTrain, Hand& boneyard, int humanScore, int computerScore, int roundNumber, int engine) {
    bool humanTurn = true;
    this->printGameState(humanPlayer, computerPlayer, mexicanTrain, boneyard, humanScore, computerScore, roundNumber, engine);

    do {
        //Check if any orphan doubles exist..
        if (checkOrphanDoubles(humanPlayer, computerPlayer, mexicanTrain) == false) {
           //If there are no orphan trains, then check if the human train has a marker, and set the human train playable if it does
            computerTrainPlayable = computerPlayer->getTrainMarker();
            this->humanTrainPlayable = true;
            this->mexicanTrainPlayable = true;
        }

        //check if user has a valid move  
        bool validMove = existsValidMove(humanPlayer, computerPlayer, mexicanTrain);
        //user has no move to play
        if (validMove == false) {
            bool skipTurn = noPlayableTiles(humanPlayer, computerPlayer, mexicanTrain, boneyard);
            if (skipTurn == false) {
                //drawn tile is not playable, skip turn after a marker is placed on train.
                humanTurn = false;
                //human turn is over
                //if the boneyard is empty, return -666 for an error code.
                if (boneyard.getSize() == 0) {
                    return -666;
                }
                continue;
            }
            else {
                //tile is playable, so restart turn and play it.
                continue;
            }
        }
        //3) Ask the user to enter a tile
        std::cout << "Player One's turn to play: \n";
        Tile userInputAsTile = playerTileChoice();
        if (userInputAsTile.getFirstNumber() == -1 && userInputAsTile.getSecondNumber() == -1) {
            continue;
        }
        //4) Ask the user for a train to play on

        char userTrain;
        std::cout << "Choose a train to play the tile on (h/H for human, c/C for computer, or m/M for mexican train): ";
        std::cin >> userTrain;
        userTrain = tolower(userTrain);

        //This functions makes sure user enters a valid train, and that it is playable.
        if (!validateTrainChoice(userTrain)) {
            continue;
        }

        bool validTileSelected = false;
        //5) Check that the tile the user played on fits on the train they chose to play on.

        //user plays on human train
        if (userTrain == 'h' && this->tileFitsOnTrain(userInputAsTile, this->getTrainEndNumber())) {
            humanPlayer->addTileToTrain(userInputAsTile);
            //if theres an orphan double, clear it
            if (humanPlayer->getOrphanDouble()) {
                humanPlayer->resetOrphanDouble();
            }
            //if theres a marker on the human train, clear it
            if (humanPlayer->getTrainMarker()) {
                humanPlayer->resetTrainMarker();
            }
            validTileSelected = true;
        }
        //user plays on computer train
        else if (userTrain == 'c' && computerPlayer->tileFitsOnTrain(userInputAsTile, computerPlayer->getTrainEndNumber())) {
            computerPlayer->addTileToTrain(userInputAsTile);
            //if theres an orphan double, clear it
            if (computerPlayer->getOrphanDouble()) {
                computerPlayer->resetOrphanDouble();
            }
            validTileSelected = true;
        }
        //user plays on mexican train
        else if(userTrain == 'm' && tileFitsOnTrain(userInputAsTile, mexicanTrain.getTrainEndNumber())) {
            mexicanTrain.addTileBack(userInputAsTile); 
            //if theres an orphan double on the mexican train, clear it
            if (mexicanTrain.getOrphanDouble()) {
                mexicanTrain.resetOrphanDouble();
            }
            validTileSelected = true;
        }

        //if human player selected invalid train and tile, restart turn
        if (validTileSelected == false) {
            continue;
        }
        //remove the tile from their han
        removeTileFromHand(userInputAsTile.getFirstNumber(), userInputAsTile.getSecondNumber());

        //check if player's hand is empty, if it is end game.
        if (humanPlayer->getHandSize() == 0) {
            std::cout << "\n\nYou Won! your hand is empty.";
            int cpuPips = computerPlayer->sumOfPips();
            return cpuPips;
        }

        //user played a double. deal with correct ruleset when they do.
        if (userInputAsTile.getFirstNumber() == userInputAsTile.getSecondNumber()) {
            playedDoubleTile(userTrain, humanPlayer, computerPlayer, mexicanTrain, boneyard);
        }

        humanTurn = false;
    } while (humanTurn);
   
    return 0;
}
   





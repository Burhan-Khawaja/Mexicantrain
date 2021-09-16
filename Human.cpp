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


Tile Human::play(bool humanTrainPlayable, bool computerTrainPlayable, bool mexicanTrainPlayable) {
    do {
        addTileToHand(Tile(9, 9));
        //HUMAN TRAIN TURN
        bool humanTurn = true;
        std::string userInput;
        
        std::cout << "Player One's turn to play: \nPlayer One's Hand: \n";
        printHand();
        std::cout << "\nChoose a tile in x-y format to play (ie - 0-0)";
        std::cin >> userInput;

        if (!verifyTileChoice(userInput)) {
            continue;
        }

        //various testing code wil between this comment and the next one.
        //computerPlayer.setOrphanDouble();//human train should be unplayable.
        //computerPlayer.setOrphanDouble();
        //computerPlayer.resetOrphanDouble();

        //end of testing code

        return Tile(userInput[0]-48, userInput[2]-48);

        
        
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
    } while (true);
}




void Human::play2Test(Player * humanPlayer, Player * computerPlayer, Train mexicanTrain)
{
    humanPlayer->play(true, false, false);
    computerPlayer->addTileToHand(Tile(1, 1));

}
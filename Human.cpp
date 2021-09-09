#include "Human.h"
#include <iostream>

Human::Human() {
    playerHand.addTile(Tile(1,1));
    playerTrain.addTileBack(Tile(0, 0));
}

void Human::addTile(Tile tileToAdd)
{
    std::cout << "Adding tile to human class.";
    playerTrain.addTileFront(tileToAdd);
}

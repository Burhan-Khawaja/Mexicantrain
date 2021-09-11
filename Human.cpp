#include "Human.h"
#include <iostream>

Human::Human() {

}

void Human::addTileToHand(Tile tileToAdd)
{
    playerHand.addTile(tileToAdd);
}

void Human::addTileToTrain(Tile tileToAdd) {
    playerTrain.addTileFront(tileToAdd);
}


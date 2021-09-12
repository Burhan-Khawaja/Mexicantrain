#include "Player.h"


void Player::printTrain()
{
    playerTrain.printTrain();
}

void Player::printHand() {
    playerHand.printHand();
}

void Player::removeTileFromHand(int value1, int value2)
{
    playerHand.removeTile(value1, value2);
}

bool Player::getTrainMarker()
{
    return playerTrain.getMarker();
}

bool Player::getOrphanDouble()
{
    return this->playerTrain.getOrphanDouble();
}

bool Player::isTrainEmpty()
{
    return this->playerTrain.isEmpty();
}


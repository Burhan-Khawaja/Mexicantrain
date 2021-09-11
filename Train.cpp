#include <iostream>
#include "Train.h"

void Train::addTileFront(Tile tileToAdd) {
    trainDeque.push_front(tileToAdd);
}

void Train::addTileBack(Tile tileToAdd) {
    trainDeque.push_back(tileToAdd);

}

Tile Train::getLastTile() {
    return trainDeque.back();
}

Tile Train::getFirstTile()
{
    return trainDeque.front();
}

void Train::getLastNumber() {

}

void Train::resetTrain() {
    trainDeque.clear();
    marker = false;
}

void Train::clearMarker()
{
    this->marker = false;
}

void Train::setMarker()
{
    this->marker = true;
}

bool Train::getMarker()
{
    return this->marker;
}

void Train::printTrain()
{
    for (int i = 0; i < trainDeque.size(); i++) {
        trainDeque[i].printTile();
        std::cout << ", ";
    }
}

void Train::setOrphanDouble()
{
    this->orphanDouble = true; 
}

void Train::resetOrphanDouble()
{
    this->orphanDouble = false;
}

bool Train::getOrphanDouble()
{
    return this->orphanDouble;
}

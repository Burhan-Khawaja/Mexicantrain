#include <iostream>
#include "Train.h"

Train::Train()
{
    trainEndNumber = -1;
    orphanDouble = false;
}

void Train::addTileFront(Tile tileToAdd) {
    trainDeque.push_front(tileToAdd);
}

void Train::addTileBack(Tile tileToAdd) {
    trainDeque.push_back(tileToAdd);

}

Tile Train::getLastTile() {
    if (trainDeque.empty()) {
        //if the train  deque is empty return a tile of value -1 -1.
        return Tile(-1, -1);
    }
    return trainDeque.back();
}

Tile Train::getFirstTile()
{
    if (trainDeque.empty()) {
        //if the train  deque is empty return a tile of value -1 -1.
        return Tile(-1, -1);
    }
    return trainDeque.front();
}

//UNIMPLEMENTED FUNCTION what is this for?>
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

bool Train::isEmpty()
{
    return this->trainDeque.empty();
}
//BURBUR need to test this code, removed engine int part.
void Train::setTrainEndNumber(int newEndNumber)
{
    /*
    if (trainDeque.empty()) {
        this->trainEndNumber = engineInt;
    }*/
    this->trainEndNumber = newEndNumber;
}

int Train::getTrainEndNumber()
{
    return this->trainEndNumber;
}

void Train::clearTrain()
{
    this->trainDeque.clear();
}

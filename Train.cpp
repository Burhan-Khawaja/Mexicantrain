#include <iostream>
#include "Train.h"

/* *********************************************************************
Function Name: Train
Purpose: Default constructor for Train object
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
Train::Train()
{
    trainDeque = {};
    trainEndNumber = -1;
    orphanDouble = false;
    marker = false;
}

/* *********************************************************************
Function Name: getOrphanDouble
Purpose: get the value of a trains orphan double
Parameters: None
Return Value: Boolean value, true if the train has an orphan double, false if it doesnt.
Assistance Received: none
********************************************************************* */
bool const Train::getOrphanDouble()
{
    return this->orphanDouble;
}

/* *********************************************************************
Function Name: getMarker
Purpose: get the value of a trains marker
Parameters: None
Return Value: Bool, true if the train has a marker, false if it doesnt
Assistance Received: none
********************************************************************* */
bool const Train::getMarker()
{
    return this->marker;
}

/* *********************************************************************
Function Name: getTrainEndNumber
Purpose: retrive the last number of a train that tiles must match to be added on.
Parameters: None
Return Value: integer value that represents the last number on the train
Assistance Received: none
********************************************************************* */
int const Train::getTrainEndNumber()
{
    return this->trainEndNumber;
}

/* *********************************************************************
Function Name: addTileFront
Purpose: add a tile to the front of the train
Parameters: tileToAdd, which is a Tile object passed by reference
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::addTileFront(Tile tileToAdd) {
    trainDeque.push_front(tileToAdd);
}

/* *********************************************************************
Function Name: setOrphanDouble
Purpose: set the boolean value of a trains orphanDouble to true
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::setOrphanDouble()
{
    this->orphanDouble = true;
}

/* *********************************************************************
Function Name: resetOrphanDouble
Purpose: set the boolean value of a trains orphanDouble to false
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::resetOrphanDouble()
{
    this->orphanDouble = false;
}


/* *********************************************************************
Function Name: addTileBack
Purpose: add a tile to the back of the train
Parameters: tileToAdd, which is a Tile object passed by reference
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::addTileBack(Tile tileToAdd) {
    //if the tiles first number is equal to the trains end number, ,
    //set the tiles second number to be the new end number
    
    if (tileToAdd.getFirstNumber() == this->getTrainEndNumber()) {
        this->setTrainEndNumber(tileToAdd.getSecondNumber());
    }
    //vice versa of the 2 comments above.
    else if (tileToAdd.getSecondNumber() == this->getTrainEndNumber()) {
        this->setTrainEndNumber(tileToAdd.getFirstNumber());
        tileToAdd.swapNumbers();
    }
    trainDeque.push_back(tileToAdd);

}

/* *********************************************************************
Function Name: resetTrain
Purpose: reset a train to a default state
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::resetTrain() {
    trainDeque.clear();
    marker = false;
}

/* *********************************************************************
Function Name: clearMarker
Purpose: set a trains marker to false
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::clearMarker()
{
    this->marker = false;
}


/* *********************************************************************
Function Name: setMarker
Purpose: set a trains marker to true
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::setMarker()
{
    this->marker = true;
}


/* *********************************************************************
Function Name: isEmpty
Purpose: check if a train is empty
Parameters: None
Return Value: Boolean value, true if the train is empty, false if it has any tiles in it.
Assistance Received: none
********************************************************************* */
bool Train::isEmpty()
{
    return this->trainDeque.empty();
}

/* *********************************************************************
Function Name: setTrainEndNumber
Purpose: set the end number of a train. The end number is the last number on the train that a tile must match in order to fit on the train
Parameters: newEndNumber, an integer value that will become the new train end number
Return Value: Boolean value, true if the train is empty, false if it has any tiles in it.
Assistance Received: none
********************************************************************* */
void Train::setTrainEndNumber(int newEndNumber)
{
    this->trainEndNumber = newEndNumber;
}

/* *********************************************************************
Function Name: clearTrain
Purpose: clear the trains vector and empty it.
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::clearTrain()
{
    this->trainDeque.clear();
}

/* *********************************************************************
Function Name: getTrainDeque
Purpose: retrieve the deque containing the tiles on the train. This is used in serialization to get the train to save to the file.
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
std::deque<Tile> Train::getTrainDeque()
{
    return this->trainDeque;
}

/* *********************************************************************
Function Name: printTrain
Purpose: print the tiles of a train to the console
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Train::printTrain()
{
    for (int i = 0; i < trainDeque.size(); i++) {
        trainDeque[i].printTile();
        std::cout << ", ";
    }
}
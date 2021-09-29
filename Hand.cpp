#include "Hand.h"
#include <iostream>
#include <algorithm>

/* *********************************************************************
Function Name: Hand
Purpose: Default constructor for hand object
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
Hand::Hand()
{
    this->m_hand = {};
}


/* *********************************************************************
Function Name: addTile
Purpose: Add a tile to our hand, which is a vecto
Parameters: tileToAdd which is an object of type Tile
Return Value: none
Algorithm: call push_back on our vector with the Tile as a parameter.
Assistance Received: none
********************************************************************* */
void Hand::addTile(Tile tileToAdd) {
    m_hand.push_back(tileToAdd);
}

/* *********************************************************************
Function Name: removeTile
Purpose: Remove a tile from our hand, based on index.
Parameters: tileToRemove - integer value that is the index we want to remove.
Return Value: none
Algorithm:
Assistance Received: none
********************************************************************* */
void Hand::removeTile(int tileToRemove) {
    m_hand.erase(m_hand.begin() + tileToRemove);
}

/* *********************************************************************
Function Name: removeTile
Purpose: Remove a tile from our hand, based on the value of the tile.
Parameters: index1- an integer that is the 1 of the 2 numbers of the tile
            index2- an integer that is the second number of the tile we want to remove
Return Value: none
Algorithm: 1)Create a tile with the 2 values given as the tiles numbers
            2)call the erase function of the vector and search the array from beginning to end for the tile we created in step 1
                when the tile is found, it will be removed.
Assistance Received: none
********************************************************************* */
void Hand::removeTile(int value1, int value2) {
    Tile tmpTile = Tile(value1, value2);
    std::vector<Tile>::iterator iteratorPos = std::find(m_hand.begin(), m_hand.end(), tmpTile);
    m_hand.erase(std::remove(m_hand.begin(), m_hand.end(), tmpTile), m_hand.end());
}

/* *********************************************************************
Function Name: printHand
Purpose: Print all the tile in a user's hand to the console.
Parameters: None
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::printHand() {
    for (int i = 0; i < m_hand.size(); i++) {
        m_hand[i].printTile();
        std::cout << ", ";
        if (i % 6 == 0 && i > 0) {
            std::cout << std::endl;
        }
    }
}

/* *********************************************************************
Function Name: getSize
Purpose: get size of users hand.
Parameters: None
Return Value: const int, the size of the users hand
Assistance Received: none
********************************************************************* */
int const Hand::getSize() {
    return m_hand.size();
}

/* *********************************************************************
Function Name: getTile
Purpose: get a tile from the hand
Parameters: index - integer value that is the index and we get the tile at that index.
Return Value: Tile object, represents the tile at the index position.
Assistance Received: none
********************************************************************* */
Tile Hand::getTile(int index) {
    return m_hand[index];
}
/* *********************************************************************
Function Name: operator[]
Purpose: Overload array indexing operators
Parameters: index, integer value of what vector spot we want to access
Return Value: the tile at the index we want to access, Tile object
Assistance Received: none
********************************************************************* */
Tile& Hand::operator[](int index) {
    return m_hand.at(index);
}

/* *********************************************************************
Function Name: clearHand
Purpose: Empty the user's hand
Parameters: None
Return Value: None
Assistance Received: none
********************************************************************* */
void Hand::clearHand()
{
    this->m_hand.clear();
}

/* *********************************************************************
Function Name: getHand
Purpose: return the vector that has the user's hand data.
Parameters: None
Return Value: Returns a copy of the user's hand, as a vector of Tile objects.
Assistance Received: none
********************************************************************* */
const std::vector<Tile> Hand::getHand()
{
    return this->m_hand;
}

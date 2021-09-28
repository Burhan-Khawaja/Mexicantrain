#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

class Hand {
public:
    /* *********************************************************************
    Function Name: Hand
    Purpose: Default constructor for hand object
    Parameters: None
    Return Value: None
    Assistance Received: none
    ********************************************************************* */
    Hand();
    /* *********************************************************************
    Function Name: addTile
    Purpose: Add a tile to our hand, which is a vecto
    Parameters: tileToAdd which is an object of type Tile
    Return Value: none
    Algorithm: call push_back on our vector with the Tile as a parameter.
    Assistance Received: none
    ********************************************************************* */
    void addTile(Tile tileToAdd);
    /* *********************************************************************
    Function Name: removeTile
    Purpose: Remove a tile from our hand, based on index.
    Parameters: tileToRemove - integer value that is the index we want to remove.
    Return Value: none
    Algorithm: 
    Assistance Received: none
    ********************************************************************* */
    void removeTile(int tileToRemove);
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
    void removeTile(int index1, int index2);
    /* *********************************************************************
    Function Name: printHand
    Purpose: Print all the tile in a user's hand to the console.
    Parameters: None
    Return Value: none
    Assistance Received: none
    ********************************************************************* */
    void printHand();
    /* *********************************************************************
    Function Name: getTile
    Purpose: get a tile from the hand
    Parameters: index - integer value that is the index and we get the tile at that index.
    Return Value: Tile object, represents the tile at the index position.
    Assistance Received: none
    ********************************************************************* */
    Tile getTile(int index);
    /* *********************************************************************
    Function Name: getSize
    Purpose: get size of users hand.
    Parameters: None
    Return Value: const int, the size of the users hand
    Assistance Received: none
    ********************************************************************* */
    int const getSize();
    /* *********************************************************************
    Function Name: operator[]
    Purpose: Overload array indexing operators
    Parameters: index, integer value of what vector spot we want to access
    Return Value: the tile at the index we want to access, Tile object
    Assistance Received: none
    ********************************************************************* */
    Tile& operator[](int index);
    /* *********************************************************************
    Function Name: clearHand
    Purpose: Empty the user's hand
    Parameters: None
    Return Value: None
    Assistance Received: none
    ********************************************************************* */
    void clearHand();
    /* *********************************************************************
    Function Name: getHand
    Purpose: return the vector that has the user's hand data.
    Parameters: None
    Return Value: Returns a copy of the user's hand, as a vector of Tile objects.
    Assistance Received: none
    ********************************************************************* */
    const std::vector<Tile> getHand();

protected:
private:
    //stores the user's tiles.
    std::vector<Tile> m_hand;
};
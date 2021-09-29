#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

class Hand {
public:
    Hand(); 
    Tile getTile(int index);
    const std::vector<Tile> getHand();
    void addTile(Tile tileToAdd);
    void removeTile(int tileToRemove);
    void removeTile(int index1, int index2);
    void printHand();
    
    int const getSize();
    Tile& operator[](int index);
    void clearHand();

protected:
private:
    //stores the user's tiles.
    std::vector<Tile> m_hand;
};
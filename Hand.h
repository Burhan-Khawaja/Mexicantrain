#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

class Hand {
public:
    void addTile(Tile tileToAdd);
    void removeTile(int tileToRemove);
    void removeTile(int index1, int index2);
    void printHand();
    Tile getTile(int);
    int getSize();
    Tile& operator[](int index);
protected:
private:
    std::vector<Tile> m_hand;
};